/**
 * @file main.c
 * @brief ESP32 HVCC Audio Integration
 * 
 * This application integrates Pure Data patches compiled with HVCC (Heavy Compiler)
 * to run on ESP32 hardware with I2S audio output.
 * 
 * Architecture:
 * - Pure Data patch (main.pd) -> HVCC compiler -> C code (output/c/)
 * - Heavy context processes audio in floating point
 * - Audio buffer converts float to int16 for I2S DAC output
 * - Runs at 48kHz stereo by default
 */

#include <stdio.h>
#include <stdbool.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/i2s_std.h"
#include "driver/gpio.h"

// Heavy (HVCC) generated Pure Data patch interface
#include "output/c/Heavy_heavy.h"
#include "output/c/HvHeavy.h"

// ============================================================================
// CONFIGURATION
// ============================================================================

static const char *TAG = "HVCC";

// Audio Configuration
#define AUDIO_SAMPLE_RATE       48000   // Hz
#define AUDIO_BLOCK_SIZE        256     // samples (must be multiple of 8 for HVCC)
#define AUDIO_BIT_DEPTH         16      // bits

// I2S Pin Configuration (adjust for your hardware)
#define I2S_PIN_WORD_SELECT     GPIO_NUM_26  // LRCK/WS
#define I2S_PIN_BIT_CLOCK       GPIO_NUM_27  // BCLK
#define I2S_PIN_DATA_OUT        GPIO_NUM_25  // DOUT to DAC

// DMA Configuration
#define I2S_DMA_DESC_COUNT      4       // number of DMA descriptors
#define I2S_DMA_FRAME_COUNT     256     // samples per descriptor

// ============================================================================
// AUDIO SUBSYSTEM
// ============================================================================

/**
 * @brief Audio system context
 * 
 * Encapsulates all state needed for audio processing pipeline
 */
typedef struct {
    i2s_chan_handle_t i2s_tx_channel;
    HeavyContextInterface *heavy_context;
    int num_output_channels;
    float *float_buffer;
    int16_t *output_buffer;
} audio_system_t;

static audio_system_t audio_sys = {0};

/**
 * @brief Initialize I2S hardware for audio output
 * 
 * Configures ESP32 I2S peripheral in master mode for stereo audio transmission
 * 
 * @return true on success, false on failure
 */
static bool audio_init_i2s(void) {
    ESP_LOGI(TAG, "Initializing I2S: %d Hz, %d-bit, stereo", 
             AUDIO_SAMPLE_RATE, AUDIO_BIT_DEPTH);
    
    // Configure I2S channel
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_AUTO, I2S_ROLE_MASTER);
    chan_cfg.dma_desc_num = I2S_DMA_DESC_COUNT;
    chan_cfg.dma_frame_num = I2S_DMA_FRAME_COUNT;
    
    esp_err_t ret = i2s_new_channel(&chan_cfg, &audio_sys.i2s_tx_channel, NULL);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create I2S channel: %s", esp_err_to_name(ret));
        return false;
    }

    // Configure I2S standard mode (Philips I2S format)
    i2s_std_config_t std_cfg = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(AUDIO_SAMPLE_RATE),
        .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(
            I2S_DATA_BIT_WIDTH_16BIT, 
            I2S_SLOT_MODE_STEREO
        ),
        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = I2S_PIN_BIT_CLOCK,
            .ws   = I2S_PIN_WORD_SELECT,
            .dout = I2S_PIN_DATA_OUT,
            .din  = I2S_GPIO_UNUSED,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv = false,
            },
        },
    };
    std_cfg.slot_cfg.slot_mask = I2S_STD_SLOT_BOTH;
    
    ret = i2s_channel_init_std_mode(audio_sys.i2s_tx_channel, &std_cfg);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize I2S standard mode: %s", esp_err_to_name(ret));
        return false;
    }

    ret = i2s_channel_enable(audio_sys.i2s_tx_channel);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to enable I2S channel: %s", esp_err_to_name(ret));
        return false;
    }

    ESP_LOGI(TAG, "I2S initialized successfully");
    return true;
}

/**
 * @brief Initialize Heavy (HVCC) audio processing context
 * 
 * Creates the Pure Data patch runtime and allocates audio buffers
 * 
 * @return true on success, false on failure
 */
static bool audio_init_heavy(void) {
    ESP_LOGI(TAG, "Initializing Heavy context...");
    
    // Create Heavy context with our sample rate
    audio_sys.heavy_context = hv_heavy_new((double)AUDIO_SAMPLE_RATE);
    if (!audio_sys.heavy_context) {
        ESP_LOGE(TAG, "Failed to create Heavy context");
        return false;
    }
    
    // Query output channel configuration
    audio_sys.num_output_channels = hv_getNumOutputChannels(audio_sys.heavy_context);
    if (audio_sys.num_output_channels <= 0) {
        ESP_LOGW(TAG, "Patch declares no output channels, defaulting to mono");
        audio_sys.num_output_channels = 1;
    }
    
    // Allocate audio processing buffers
    size_t float_buffer_size = AUDIO_BLOCK_SIZE * audio_sys.num_output_channels;
    audio_sys.float_buffer = (float *)malloc(float_buffer_size * sizeof(float));
    
    size_t output_buffer_size = AUDIO_BLOCK_SIZE * 2;  // stereo
    audio_sys.output_buffer = (int16_t *)malloc(output_buffer_size * sizeof(int16_t));
    
    if (!audio_sys.float_buffer || !audio_sys.output_buffer) {
        ESP_LOGE(TAG, "Failed to allocate audio buffers");
        return false;
    }
    
    ESP_LOGI(TAG, "Heavy context ready: %d channels, %d samples/block", 
             audio_sys.num_output_channels, AUDIO_BLOCK_SIZE);
    return true;
}

/**
 * @brief Clip audio sample to prevent distortion
 * 
 * @param sample Input sample value
 * @return Clipped sample in range [-1.0, 1.0]
 */
static inline float audio_clip_sample(float sample) {
    if (sample > 1.0f) return 1.0f;
    if (sample < -1.0f) return -1.0f;
    return sample;
}

/**
 * @brief Convert float audio to int16 and interleave stereo
 * 
 * Takes planar float audio from Heavy and converts to interleaved
 * int16 stereo format required by I2S DAC
 * 
 * @param float_in Input float buffer (planar)
 * @param int16_out Output int16 buffer (interleaved stereo)
 * @param num_frames Number of audio frames to convert
 */
static void audio_convert_to_i2s_format(const float *float_in, int16_t *int16_out, 
                                         int num_frames) {
    for (int i = 0; i < num_frames; i++) {
        // Get left channel
        float left = audio_clip_sample(float_in[i]);
        
        // Get right channel (duplicate left if mono)
        float right = (audio_sys.num_output_channels >= 2) 
                      ? audio_clip_sample(float_in[i + num_frames])
                      : left;
        
        // Convert to int16 and interleave: [L, R, L, R, ...]
        int16_out[2 * i]     = (int16_t)(left * 32767.0f);
        int16_out[2 * i + 1] = (int16_t)(right * 32767.0f);
    }
}

/**
 * @brief Main audio processing and output loop
 * 
 * Continuously processes audio through Heavy context and outputs to I2S.
 * This function never returns.
 */
static void audio_processing_loop(void) {
    ESP_LOGI(TAG, "Starting audio processing loop");
    
    size_t bytes_to_write = AUDIO_BLOCK_SIZE * 2 * sizeof(int16_t);  // stereo
    size_t bytes_written;
    
    while (true) {
        // Process audio block through Heavy (Pure Data) patch
        int frames_processed = hv_processInline(
            audio_sys.heavy_context,
            NULL,                       // no input
            audio_sys.float_buffer,     // output buffer
            AUDIO_BLOCK_SIZE            // frames to process
        );
        
        if (frames_processed <= 0) {
            // No audio generated, yield to other tasks
            vTaskDelay(pdMS_TO_TICKS(1));
            continue;
        }
        
        // Convert float to int16 and interleave for I2S
        audio_convert_to_i2s_format(
            audio_sys.float_buffer,
            audio_sys.output_buffer,
            frames_processed
        );
        
        // Write to I2S DAC
        esp_err_t ret = i2s_channel_write(
            audio_sys.i2s_tx_channel,
            audio_sys.output_buffer,
            bytes_to_write,
            &bytes_written,
            portMAX_DELAY
        );
        
        if (ret != ESP_OK || bytes_written != bytes_to_write) {
            ESP_LOGW(TAG, "I2S write incomplete: %d bytes of %d", 
                     bytes_written, bytes_to_write);
            vTaskDelay(pdMS_TO_TICKS(1));
        }
    }
}

// ============================================================================
// MAIN APPLICATION
// ============================================================================

/**
 * @brief Application entry point
 * 
 * Initializes audio subsystem and starts processing loop
 */
void app_main(void) {
    ESP_LOGI(TAG, "========================================");
    ESP_LOGI(TAG, "ESP32 HVCC Audio Application Starting");
    ESP_LOGI(TAG, "========================================");
    
    // Initialize I2S hardware
    if (!audio_init_i2s()) {
        ESP_LOGE(TAG, "I2S initialization failed - halting");
        return;
    }
    
    // Initialize Heavy (Pure Data) audio engine
    if (!audio_init_heavy()) {
        ESP_LOGE(TAG, "Heavy initialization failed - halting");
        return;
    }
    
    ESP_LOGI(TAG, "All systems ready - starting audio output");
    ESP_LOGI(TAG, "========================================");
    
    // Run audio loop (never returns)
    audio_processing_loop();
}
