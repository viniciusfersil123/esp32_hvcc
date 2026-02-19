#include <math.h>
#include "driver/i2s_std.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// ============================================================================
// Configuration and State
// ============================================================================
#define SAMPLE_RATE 48000
#define SINE_FREQUENCY 220.0f
#define VOLUME_SCALE 0.5f

static i2s_chan_handle_t tx_handle = NULL;
static float phase = 0.0f;
static float phase_increment = 0.0f;

// ============================================================================
// I2S Audio Initialization
// ============================================================================
static void audio_init(void)
{
    const i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(
        I2S_NUM_AUTO,
        I2S_ROLE_MASTER
    );

    const i2s_std_config_t i2s_config = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(SAMPLE_RATE),
        .slot_cfg = I2S_STD_MSB_SLOT_DEFAULT_CONFIG(
            I2S_DATA_BIT_WIDTH_16BIT,
            I2S_SLOT_MODE_STEREO
        ),
        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = GPIO_NUM_27,
            .ws = GPIO_NUM_26,
            .dout = GPIO_NUM_25,
            .din = I2S_GPIO_UNUSED,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv = false,
            },
        },
    };

    i2s_new_channel(&chan_cfg, &tx_handle, NULL);
    i2s_channel_init_std_mode(tx_handle, &i2s_config);
    i2s_channel_enable(tx_handle);

    // Pre-calculate phase increment for sine wave generation
    phase_increment = (2.0f * M_PI * SINE_FREQUENCY) / SAMPLE_RATE;
}

// ============================================================================
// Audio Signal Generation
// ============================================================================
static float generate_sine(void)
{
    float sample = sinf(phase) * VOLUME_SCALE;
    phase += phase_increment;
    
    // Wrap phase to prevent overflow
    if (phase > 2.0f * M_PI) {
        phase -= 2.0f * M_PI;
    }
    
    return sample;
}

// ============================================================================
// Audio Write
// ============================================================================
static void audio_write(float left, float right)
{
    int16_t left_sample = (int16_t)(left * 32767.0f);
    int16_t right_sample = (int16_t)(right * 32767.0f);

    int16_t buffer[2] = { left_sample, right_sample };
    size_t bytes_written = 0;

    i2s_channel_write(tx_handle, buffer, sizeof(buffer), &bytes_written, portMAX_DELAY);
}

// ============================================================================
// Main Application
// ============================================================================
void app_main(void)
{
    audio_init();

    while (1) {
        float sine_sample = generate_sine();
        audio_write(sine_sample, sine_sample);
    }
}