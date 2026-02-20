/**
 * AUTO-GENERATED CONTROLS IMPLEMENTATION
 * Generated from board_config.json
 * 
 * This file is regenerated on each build - do not edit directly
 */

#include "controls_generated.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"

static const char *TAG = "Controls";

// ============================================================================
// ADC CONTROL DATA
// ============================================================================


adc_oneshot_unit_handle_t adc_handle = NULL;

adc_control_t adc_controls[NUM_ADCS] = {

    {
        .channel = ADC_KNOB1_CHANNEL,
        .receiver = ADC_KNOB1_RECEIVER,
        .name = "knob1",
        .hash = 0,  // Will be set during init
    },

};

/**
 * @brief Initialize all ADC controls
 */
bool controls_init_adc(HeavyContextInterface *hv_ctx) {
    ESP_LOGI(TAG, "Initializing %d ADC control(s)", NUM_ADCS);
    
    if (NUM_ADCS == 0) {
        ESP_LOGW(TAG, "No ADC controls configured");
        return true;
    }
    
    // Create ADC unit
    adc_oneshot_unit_init_cfg_t unit_cfg = {
        .unit_id = ADC_UNIT_1,
    };
    
    esp_err_t ret = adc_oneshot_new_unit(&unit_cfg, &adc_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create ADC unit: %s", esp_err_to_name(ret));
        return false;
    }
    
    // Configure each ADC channel
    for (int i = 0; i < NUM_ADCS; i++) {
        adc_oneshot_chan_cfg_t chan_cfg = {
            .bitwidth = ADC_BITWIDTH_12,
            .atten = ADC_ATTEN_DB_12,
        };
        
        ret = adc_oneshot_config_channel(adc_handle, adc_controls[i].channel, &chan_cfg);
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "Failed to configure ADC channel %d: %s", 
                     adc_controls[i].channel, esp_err_to_name(ret));
            return false;
        }
        
        // Pre-compute receiver hashes
        adc_controls[i].hash = hv_stringToHash(adc_controls[i].receiver);
        
        ESP_LOGI(TAG, "  [%d] %s -> %s (GPIO%d)", 
                 i, adc_controls[i].name, adc_controls[i].receiver,

                 i == 0 ? 33 :

                 0);
    }
    
    ESP_LOGI(TAG, "ADC controls initialized");
    return true;
}



// ============================================================================
// BUTTON CONTROL DATA
// ============================================================================



#define BTN_DEBOUNCE_SAMPLES 3

typedef struct {
    gpio_num_t pin;
    const char *receiver;
    hv_uint32_t hash;
    bool invert;
    bool stable_state;
    bool last_sample;
    uint8_t stable_count;
} button_control_t;

button_control_t button_controls[NUM_BUTTONS] = {

    {
        .pin = BTN_BUTTON1_PIN,
        .receiver = BTN_BUTTON1_RECEIVER,
        .hash = 0,
        .invert = (BTN_BUTTON1_INVERT != 0),
        .stable_state = false,
        .last_sample = false,
        .stable_count = 0,
    },

};

/**
 * @brief Initialize all button controls
 */
bool controls_init_buttons(void) {
    ESP_LOGI(TAG, "Initializing %d button control(s)", NUM_BUTTONS);

    if (NUM_BUTTONS == 0) {
        ESP_LOGW(TAG, "No button controls configured");
        return true;
    }

    for (int i = 0; i < NUM_BUTTONS; i++) {
        gpio_config_t io_conf = {
            .pin_bit_mask = (1ULL << button_controls[i].pin),
            .mode = GPIO_MODE_INPUT,
            .pull_up_en = button_controls[i].invert ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE,
            .pull_down_en = button_controls[i].invert ? GPIO_PULLDOWN_DISABLE : GPIO_PULLDOWN_ENABLE,
            .intr_type = GPIO_INTR_DISABLE,
        };

        esp_err_t ret = gpio_config(&io_conf);
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "Failed to configure button GPIO %d: %s",
                     button_controls[i].pin, esp_err_to_name(ret));
            return false;
        }

        // Pre-compute receiver hashes
        button_controls[i].hash = hv_stringToHash(button_controls[i].receiver);

        // Initialize debounce state
        bool raw = gpio_get_level(button_controls[i].pin);
        bool pressed = button_controls[i].invert ? !raw : raw;
        button_controls[i].stable_state = pressed;
        button_controls[i].last_sample = pressed;
        button_controls[i].stable_count = BTN_DEBOUNCE_SAMPLES;

        ESP_LOGI(TAG, "  [%d] %s -> %s (GPIO%d, invert=%d)",
                 i,

                 i == 0 ? "button1" :

                 "?",
                 button_controls[i].receiver,
                 button_controls[i].pin,
                 button_controls[i].invert ? 1 : 0);
    }

    ESP_LOGI(TAG, "Button controls initialized");
    return true;
}



// ============================================================================
// CONTROL POLLING TASK
// ============================================================================



/**
 * @brief Controls polling task
 */
void controls_task(void *arg) {
    HeavyContextInterface *hv_ctx = (HeavyContextInterface *)arg;
    
    ESP_LOGI(TAG, "Starting controls polling task");
    
    while (true) {

        // Poll each ADC
        for (int i = 0; i < NUM_ADCS; i++) {
            int adc_raw = 0;
            esp_err_t ret = adc_oneshot_read(adc_handle, adc_controls[i].channel, &adc_raw);
            
            if (ret == ESP_OK) {
                // Convert raw (0-4095) to float (0.0-1.0)
                float value = (float)adc_raw / 4095.0f;
                
                // Send to Pure Data receiver
                hv_sendFloatToReceiver(hv_ctx, adc_controls[i].hash, value);
            } else {
                ESP_LOGW(TAG, "ADC read failed for %s: %s", 
                         adc_controls[i].name, esp_err_to_name(ret));
            }
        }



        // Poll each button (debounced)
        for (int i = 0; i < NUM_BUTTONS; i++) {
            bool raw = gpio_get_level(button_controls[i].pin);
            bool pressed = button_controls[i].invert ? !raw : raw;

            if (pressed == button_controls[i].last_sample) {
                if (button_controls[i].stable_count < BTN_DEBOUNCE_SAMPLES) {
                    button_controls[i].stable_count++;
                }
            } else {
                button_controls[i].last_sample = pressed;
                button_controls[i].stable_count = 0;
            }

            if (button_controls[i].stable_count >= BTN_DEBOUNCE_SAMPLES) {
                if (pressed != button_controls[i].stable_state) {
                    button_controls[i].stable_state = pressed;
                    // Only send event on press (when state becomes true/1)
                    if (button_controls[i].stable_state) {
                        hv_sendFloatToReceiver(
                            hv_ctx,
                            button_controls[i].hash,
                            1.0f
                        );
                    }
                }
            }
        }

        
        // Poll rate
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

