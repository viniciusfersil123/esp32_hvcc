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
#define ADC_KNOB1_RECEIVER      "knob2"
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
 * @brief ADC polling task
 * 
 * Reads ADC values and sends to Pure Data receivers
 * 
 * @param arg Unused
 */
void controls_task(void *arg);




// ============================================================================
// BUTTON CONTROL MAPPINGS
// ============================================================================


#define BTN_BUTTON1_PIN          GPIO_NUM_32
#define BTN_BUTTON1_RECEIVER     "button1"
#define BTN_BUTTON1_INVERT       1




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