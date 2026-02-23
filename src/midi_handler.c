/**
 * @file midi_handler.c
 * @brief MIDI Protocol Handler Implementation
 * 
 * ESP32 implementation of MIDI I/O for Heavy/Pure Data integration
 */

#include "midi_handler.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include <string.h>

static const char *TAG = "MIDI";

// MIDI state
static struct {
    bool initialized;
    midi_config_t config;
    HeavyContextInterface *heavy_context;
    uint8_t tx_fifo[MIDI_OUT_FIFO_SIZE];
    uint16_t tx_fifo_head;
    uint16_t tx_fifo_tail;
    uint8_t running_status;
} midi_state = {0};

// Heavy MIDI receiver hashes (from HvHeavy.h)
#ifndef HV_HASH_NOTEIN
#define HV_HASH_NOTEIN 0x67E37CA3
#endif
#ifndef HV_HASH_CTLIN
#define HV_HASH_CTLIN 0x41BE0F9C
#endif
#ifndef HV_HASH_PGMIN
#define HV_HASH_PGMIN 0x2E1EA03D
#endif
#ifndef HV_HASH_TOUCHIN
#define HV_HASH_TOUCHIN 0x553925BD
#endif
#ifndef HV_HASH_BENDIN
#define HV_HASH_BENDIN 0xE7C09E93
#endif
#ifndef HV_HASH_MIDIIN
#define HV_HASH_MIDIIN 0x0AAECD5C
#endif
#ifndef HV_HASH_MIDIREALTIMEIN
#define HV_HASH_MIDIREALTIMEIN 0x890A45E6
#endif

// Heavy MIDI sender hashes
#ifndef HV_HASH_NOTEOUT
#define HV_HASH_NOTEOUT 0xD1D4AC2
#endif
#ifndef HV_HASH_CTLOUT
#define HV_HASH_CTLOUT 0xE5E2A040
#endif
#ifndef HV_HASH_PGMOUT
#define HV_HASH_PGMOUT 0x8753E39E
#endif
#ifndef HV_HASH_TOUCHOUT
#define HV_HASH_TOUCHOUT 0x0B84AFE1
#endif
#ifndef HV_HASH_BENDOUT
#define HV_HASH_BENDOUT 0xE8458013
#endif
#ifndef HV_HASH_POLYTOUCHOUT
#define HV_HASH_POLYTOUCHOUT 0xBC530F59
#endif
#ifndef HV_HASH_MIDIOUT
#define HV_HASH_MIDIOUT 0x49AA79A9
#endif

/**
 * @brief Write byte to MIDI TX FIFO
 */
static bool midi_fifo_write(uint8_t byte) {
    uint16_t next_head = (midi_state.tx_fifo_head + 1) % MIDI_OUT_FIFO_SIZE;
    if (next_head == midi_state.tx_fifo_tail) {
        return false; // FIFO full
    }
    midi_state.tx_fifo[midi_state.tx_fifo_head] = byte;
    midi_state.tx_fifo_head = next_head;
    return true;
}

/**
 * @brief Read byte from MIDI TX FIFO
 */
static bool midi_fifo_read(uint8_t *byte) {
    if (midi_state.tx_fifo_head == midi_state.tx_fifo_tail) {
        return false; // FIFO empty
    }
    *byte = midi_state.tx_fifo[midi_state.tx_fifo_tail];
    midi_state.tx_fifo_tail = (midi_state.tx_fifo_tail + 1) % MIDI_OUT_FIFO_SIZE;
    return true;
}

/**
 * @brief Initialize UART for MIDI
 */
static bool midi_init_uart(void) {
    const uart_config_t uart_config = {
        .baud_rate = MIDI_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    esp_err_t ret = uart_driver_install(MIDI_UART_NUM, 
                                        MIDI_RX_BUFFER_SIZE, 
                                        MIDI_TX_BUFFER_SIZE, 
                                        0, NULL, 0);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to install UART driver: %s", esp_err_to_name(ret));
        return false;
    }

    ret = uart_param_config(MIDI_UART_NUM, &uart_config);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure UART: %s", esp_err_to_name(ret));
        return false;
    }

    ret = uart_set_pin(MIDI_UART_NUM, 
                      midi_state.config.uart_tx_pin,
                      midi_state.config.uart_rx_pin,
                      UART_PIN_NO_CHANGE,
                      UART_PIN_NO_CHANGE);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set UART pins: %s", esp_err_to_name(ret));
        return false;
    }

    ESP_LOGI(TAG, "MIDI UART initialized on TX:%d RX:%d at %d baud", 
             midi_state.config.uart_tx_pin, 
             midi_state.config.uart_rx_pin,
             MIDI_BAUD_RATE);
    return true;
}

bool midi_init(const midi_config_t *config, HeavyContextInterface *heavy_context) {
    if (midi_state.initialized) {
        ESP_LOGW(TAG, "MIDI already initialized");
        return true;
    }

    if (!config || !heavy_context) {
        ESP_LOGE(TAG, "Invalid configuration or Heavy context");
        return false;
    }

    memcpy(&midi_state.config, config, sizeof(midi_config_t));
    midi_state.heavy_context = heavy_context;
    midi_state.tx_fifo_head = 0;
    midi_state.tx_fifo_tail = 0;
    midi_state.running_status = 0;

    bool success = false;
    switch (config->transport) {
        case MIDI_TRANSPORT_UART:
            success = midi_init_uart();
            break;
        case MIDI_TRANSPORT_USB:
            ESP_LOGE(TAG, "USB MIDI not yet implemented");
            success = false;
            break;
        default:
            ESP_LOGE(TAG, "Invalid MIDI transport type");
            success = false;
            break;
    }

    if (success) {
        midi_state.initialized = true;
        ESP_LOGI(TAG, "MIDI handler ready (input:%d output:%d)", 
                 config->enable_input, config->enable_output);
    }

    return success;
}

/**
 * @brief Process incoming MIDI byte and dispatch to Heavy
 */
static void midi_process_input_byte(uint8_t byte) {
    static uint8_t message[3];
    static uint8_t message_len = 0;
    static uint8_t expected_len = 0;
    static uint8_t status_byte = 0;

    // System realtime messages (single byte, can interrupt other messages)
    if (byte >= MIDI_RT_CLOCK) {
        hv_sendMessageToReceiverV(midi_state.heavy_context, HV_HASH_MIDIREALTIMEIN, 0, "f", (float)byte);
        return;
    }

    // Status byte (MSB set)
    if (byte & 0x80) {
        status_byte = byte;
        midi_state.running_status = byte;
        message[0] = byte;
        message_len = 1;

        // Determine expected message length
        uint8_t type = status_byte & 0xF0;
        switch (type) {
            case MIDI_NOTE_OFF:
            case MIDI_NOTE_ON:
            case MIDI_POLY_AFTERTOUCH:
            case MIDI_CONTROL_CHANGE:
            case MIDI_PITCH_BEND:
                expected_len = 3;
                break;
            case MIDI_PROGRAM_CHANGE:
            case MIDI_AFTERTOUCH:
                expected_len = 2;
                break;
            default:
                expected_len = 1; // System messages
                break;
        }
        return;
    }

    // Data byte (running status or continuation)
    if (status_byte == 0) {
        status_byte = midi_state.running_status;
        message[0] = status_byte;
        message_len = 1;
    }

    if (message_len < 3) {
        message[message_len++] = byte;
    }

    // Process complete message
    if (message_len >= expected_len) {
        uint8_t type = status_byte & 0xF0;
        uint8_t channel = status_byte & 0x0F;
        uint8_t data1 = (message_len > 1) ? message[1] : 0;
        uint8_t data2 = (message_len > 2) ? message[2] : 0;

        // Send raw MIDI data to [midiin]
        for (int i = 0; i < message_len; i++) {
            hv_sendMessageToReceiverV(midi_state.heavy_context, HV_HASH_MIDIIN, 0, "ff",
                                     (float)message[i], (float)channel);
        }

        // Send parsed messages to specific receivers
        switch (type) {
            case MIDI_NOTE_ON:
            case MIDI_NOTE_OFF: {
                uint8_t velocity = (type == MIDI_NOTE_OFF) ? 0 : data2;
                hv_sendMessageToReceiverV(midi_state.heavy_context, HV_HASH_NOTEIN, 0, "fff",
                                         (float)data1, (float)velocity, (float)channel);
                break;
            }
            case MIDI_CONTROL_CHANGE:
                hv_sendMessageToReceiverV(midi_state.heavy_context, HV_HASH_CTLIN, 0, "fff",
                                         (float)data2, (float)data1, (float)channel);
                break;
            case MIDI_PROGRAM_CHANGE:
                hv_sendMessageToReceiverV(midi_state.heavy_context, HV_HASH_PGMIN, 0, "ff",
                                         (float)data1, (float)channel);
                break;
            case MIDI_AFTERTOUCH:
                hv_sendMessageToReceiverV(midi_state.heavy_context, HV_HASH_TOUCHIN, 0, "ff",
                                         (float)data1, (float)channel);
                break;
            case MIDI_PITCH_BEND: {
                uint16_t bend = (data2 << 7) | data1;
                hv_sendMessageToReceiverV(midi_state.heavy_context, HV_HASH_BENDIN, 0, "ff",
                                         (float)bend, (float)channel);
                break;
            }
            case MIDI_POLY_AFTERTOUCH:
                // Note: Heavy doesn't have a standard polytouchin, send to midiin
                break;
        }

        // Reset for next message
        message_len = 0;
        if (type != MIDI_SYSTEM) {
            // Keep running status for channel messages
            status_byte = midi_state.running_status;
        } else {
            status_byte = 0;
        }
    }
}

void midi_process(void) {
    if (!midi_state.initialized || !midi_state.config.enable_input) {
        return;
    }

    // Process incoming MIDI (UART)
    if (midi_state.config.transport == MIDI_TRANSPORT_UART) {
        uint8_t byte;
        while (uart_read_bytes(MIDI_UART_NUM, &byte, 1, 0) == 1) {
            midi_process_input_byte(byte);
        }
    }

    // Flush outgoing MIDI
    if (midi_state.config.enable_output) {
        uint8_t byte;
        while (midi_fifo_read(&byte)) {
            if (midi_state.config.transport == MIDI_TRANSPORT_UART) {
                uart_write_bytes(MIDI_UART_NUM, &byte, 1);
            }
        }
    }
}

bool midi_send(const uint8_t *data, uint8_t length) {
    if (!midi_state.initialized || !midi_state.config.enable_output) {
        return false;
    }

    for (uint8_t i = 0; i < length; i++) {
        if (!midi_fifo_write(data[i])) {
            ESP_LOGW(TAG, "MIDI TX FIFO full");
            return false;
        }
    }

    return true;
}

void midi_handle_heavy_send(uint32_t sendHash, const HvMessage *m) {
    if (!midi_state.initialized || !midi_state.config.enable_output) {
        return;
    }

    uint8_t midiData[3];
    uint8_t numBytes = 0;

    switch (sendHash) {
        case HV_HASH_NOTEOUT: {
            uint8_t note = (uint8_t)hv_msg_getFloat(m, 0);
            uint8_t velocity = (uint8_t)hv_msg_getFloat(m, 1);
            uint8_t ch = (uint8_t)hv_msg_getFloat(m, 2) % 16;

            midiData[0] = (velocity > 0 ? MIDI_NOTE_ON : MIDI_NOTE_OFF) | ch;
            midiData[1] = note;
            midiData[2] = velocity;
            numBytes = 3;
            break;
        }
        case HV_HASH_CTLOUT: {
            uint8_t value = (uint8_t)hv_msg_getFloat(m, 0);
            uint8_t cc = (uint8_t)hv_msg_getFloat(m, 1);
            uint8_t ch = (uint8_t)hv_msg_getFloat(m, 2) % 16;

            midiData[0] = MIDI_CONTROL_CHANGE | ch;
            midiData[1] = cc;
            midiData[2] = value;
            numBytes = 3;
            break;
        }
        case HV_HASH_PGMOUT: {
            uint8_t pgm = (uint8_t)hv_msg_getFloat(m, 0);
            uint8_t ch = (uint8_t)hv_msg_getFloat(m, 1) % 16;

            midiData[0] = MIDI_PROGRAM_CHANGE | ch;
            midiData[1] = pgm;
            numBytes = 2;
            break;
        }
        case HV_HASH_TOUCHOUT: {
            uint8_t value = (uint8_t)hv_msg_getFloat(m, 0);
            uint8_t ch = (uint8_t)hv_msg_getFloat(m, 1) % 16;

            midiData[0] = MIDI_AFTERTOUCH | ch;
            midiData[1] = value;
            numBytes = 2;
            break;
        }
        case HV_HASH_BENDOUT: {
            uint16_t value = (uint16_t)hv_msg_getFloat(m, 0);
            uint8_t ch = (uint8_t)hv_msg_getFloat(m, 1) % 16;

            midiData[0] = MIDI_PITCH_BEND | ch;
            midiData[1] = value & 0x7F;        // LSB
            midiData[2] = (value >> 7) & 0x7F; // MSB
            numBytes = 3;
            break;
        }
        case HV_HASH_POLYTOUCHOUT: {
            uint8_t value = (uint8_t)hv_msg_getFloat(m, 0);
            uint8_t note = (uint8_t)hv_msg_getFloat(m, 1);
            uint8_t ch = (uint8_t)hv_msg_getFloat(m, 2) % 16;

            midiData[0] = MIDI_POLY_AFTERTOUCH | ch;
            midiData[1] = note;
            midiData[2] = value;
            numBytes = 3;
            break;
        }
        case HV_HASH_MIDIOUT: {
            // Raw MIDI bytes from [midiout]
            // This typically comes in multiple calls, but we'll handle single bytes
            midiData[0] = (uint8_t)hv_msg_getFloat(m, 0);
            numBytes = 1;
            break;
        }
        default:
            return; // Not a MIDI message
    }

    if (numBytes > 0) {
        midi_send(midiData, numBytes);
    }
}

bool midi_is_ready(void) {
    return midi_state.initialized;
}
