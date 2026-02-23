/**
 * @file midi_handler.h
 * @brief MIDI Protocol Handler for ESP32 HVCC
 * 
 * Implements MIDI input/output for Heavy/Pure Data patches on ESP32.
 * Based on libdaisy and pd2dsy MIDI implementation patterns.
 * 
 * Supports:
 * - MIDI UART (hardware serial)
 * - USB MIDI (via TinyUSB)
 * - Standard MIDI messages (note, CC, program change, etc.)
 * - Heavy receiver integration ([notein], [ctlin], [pgmin], etc.)
 * - Heavy sender integration ([noteout], [ctlout], [pgmout], etc.)
 */

#ifndef MIDI_HANDLER_H
#define MIDI_HANDLER_H

#include <stdint.h>
#include <stdbool.h>
#include "output/c/Heavy_heavy.h"
#include "output/c/HvHeavy.h"

#ifdef __cplusplus
extern "C" {
#endif

// MIDI Configuration
#define MIDI_UART_NUM           UART_NUM_2
#define MIDI_BAUD_RATE          31250
#define MIDI_RX_BUFFER_SIZE     256
#define MIDI_TX_BUFFER_SIZE     256
#define MIDI_OUT_FIFO_SIZE      256

// MIDI message types
#define MIDI_NOTE_OFF           0x80
#define MIDI_NOTE_ON            0x90
#define MIDI_POLY_AFTERTOUCH    0xA0
#define MIDI_CONTROL_CHANGE     0xB0
#define MIDI_PROGRAM_CHANGE     0xC0
#define MIDI_AFTERTOUCH         0xD0
#define MIDI_PITCH_BEND         0xE0
#define MIDI_SYSTEM             0xF0

// MIDI realtime messages
#define MIDI_RT_CLOCK           0xF8
#define MIDI_RT_START           0xFA
#define MIDI_RT_CONTINUE        0xFB
#define MIDI_RT_STOP            0xFC
#define MIDI_RT_ACTIVE_SENSE    0xFE
#define MIDI_RT_RESET           0xFF

/**
 * @brief MIDI transport type
 */
typedef enum {
    MIDI_TRANSPORT_NONE = 0,
    MIDI_TRANSPORT_UART,
    MIDI_TRANSPORT_USB
} midi_transport_t;

/**
 * @brief MIDI configuration
 */
typedef struct {
    midi_transport_t transport;  ///< Transport type
    uint8_t uart_tx_pin;         ///< UART TX pin (for UART transport)
    uint8_t uart_rx_pin;         ///< UART RX pin (for UART transport)
    bool enable_input;           ///< Enable MIDI input
    bool enable_output;          ///< Enable MIDI output
} midi_config_t;

/**
 * @brief Initialize MIDI handler
 * 
 * @param config MIDI configuration
 * @param heavy_context Heavy context for message routing
 * @return true on success, false on failure
 */
bool midi_init(const midi_config_t *config, HeavyContextInterface *heavy_context);

/**
 * @brief Process incoming MIDI messages
 * 
 * Call this regularly (e.g., from main loop) to handle incoming MIDI data
 */
void midi_process(void);

/**
 * @brief Send MIDI message
 * 
 * @param data MIDI message bytes
 * @param length Number of bytes (1-3 typically)
 * @return true on success, false if buffer full
 */
bool midi_send(const uint8_t *data, uint8_t length);

/**
 * @brief Heavy send hook for MIDI output
 * 
 * This should be called from the Heavy send hook to handle MIDI output
 * messages from Pure Data (noteout, ctlout, etc.)
 * 
 * @param sendHash Hash of the receiver name
 * @param m Heavy message
 */
void midi_handle_heavy_send(uint32_t sendHash, const HvMessage *m);

/**
 * @brief Get MIDI configuration status
 * 
 * @return true if MIDI is initialized and ready
 */
bool midi_is_ready(void);

#ifdef __cplusplus
}
#endif

#endif // MIDI_HANDLER_H
