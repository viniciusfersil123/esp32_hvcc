/**
 * AUTO-GENERATED CONTROLS CODE
 * Generated from board_config.json
 * 
 * This file is regenerated on each build - do not edit directly
 */

#ifndef GENERATED_CONTROLS_H
#define GENERATED_CONTROLS_H

#include <stdbool.h>
#include "esp_adc/adc_oneshot.h"
#include "output/c/HvHeavy.h"

// ============================================================================
// ADC CONTROL MAPPINGS
// ============================================================================


#define ADC_KNOB1_PIN           GPIO_NUM_33
#define ADC_KNOB1_UNIT          ADC_UNIT_1
#define ADC_KNOB1_CHANNEL       ADC_CHANNEL_5
#define ADC_KNOB1_RECEIVER      "knob1"
#define ADC_KNOB1_DESCRIPTION  "Main knob control"


#define NUM_ADCS 1


// ADC configuration structures
typedef struct {
    adc_channel_t channel;
    const char *receiver;
    const char *name;
    hv_uint32_t hash;
} adc_control_t;

extern adc_control_t adc_controls[NUM_ADCS];
extern adc_oneshot_unit_handle_t adc_handle;

// ============================================================================
// ADC CONTROL FUNCTIONS
// ============================================================================

/**
 * @brief Initialize all ADC controls
 * 
 * Configures ADC units and channels for control inputs
 * 
 * @param hv_ctx Heavy context for receiver hashing
 * @return true on success, false on failure
 */
bool controls_init_adc(HeavyContextInterface *hv_ctx);

/**
 * @brief Poll ADC values and send to Pure Data receivers
 * 
 * Call this from the main audio loop for synchronized sampling
 * 
 * @param hv_ctx Heavy context
 */
void controls_poll_adc(HeavyContextInterface *hv_ctx);

/**
 * @brief Button polling task (debouncing)
 * 
 * Reads button values with debouncing and sends to Pure Data receivers
 * Should run as a separate task with 10ms polling interval
 * 
 * @param arg Heavy context
 */
void controls_task_buttons_only(void *arg);

/**
 * @brief Unified controls task (calls button polling)
 * 
 * Legacy compatibility function that delegates to button-only task
 * ADC polling is now done in the main audio loop
 * 
 * @param arg Heavy context
 */
void controls_task(void *arg);




// ============================================================================
// BUTTON CONTROL MAPPINGS
// ============================================================================

#define BTN_MODE_BANG            0
#define BTN_MODE_FLOAT           1


#define BTN_BUTTON1_PIN          GPIO_NUM_32
#define BTN_BUTTON1_RECEIVER     "button1"
#define BTN_BUTTON1_INVERT       1
#define BTN_BUTTON1_MODE         BTN_MODE_BANG




#define NUM_BUTTONS 1

// ============================================================================
// BUTTON CONTROL FUNCTIONS
// ============================================================================

/**
 * @brief Initialize all button controls
 * 
 * Configures GPIOs for button inputs
 * 
 * @return true on success, false on failure
 */
bool controls_init_buttons(void);

#endif // GENERATED_CONTROLS_H