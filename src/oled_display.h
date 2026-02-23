/**
 * @file oled_display.h
 * @brief OLED Display Interface for SSD1306
 * 
 * Simple display driver for showing system information and Hello World
 * on a 128x64 SPI OLED display.
 */

#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Display dimensions
#define OLED_WIDTH      128
#define OLED_HEIGHT     64

// Maximum number of displays
#define OLED_MAX_DISPLAYS 2

/**
 * @brief Configuration for a single OLED display
 */
typedef struct {
    uint8_t id;              ///< Display ID (0 or 1)
    uint8_t cs_pin;          ///< Chip Select pin
    char table_name[32];     ///< Pure Data table name to display (empty if none)
    float value_min;         ///< Minimum value for scaling (default: 0)
    float value_max;         ///< Maximum value for scaling (default: 1)
} oled_display_config_t;

/**
 * @brief OLED system configuration
 */
typedef struct {
    uint8_t mosi_pin;        ///< SPI MOSI pin
    uint8_t clk_pin;         ///< SPI Clock pin
    uint8_t dc_pin;          ///< Data/Command pin
    uint8_t rst_pin;         ///< Reset pin
    uint8_t num_displays;    ///< Number of displays (1 or 2)
    oled_display_config_t displays[OLED_MAX_DISPLAYS];
} oled_config_t;

/**
 * @brief Initialize OLED displays with configuration
 * 
 * Sets up SPI communication and initializes SSD1306 display(s)
 * 
 * @param config Pointer to OLED configuration
 * @return true on success, false on failure
 */
bool oled_init(const oled_config_t *config);

/**
 * @brief Update display with Hello World and random info
 * 
 * @param display_id Display ID (OLED_DISPLAY_1 or OLED_DISPLAY_2)
 */
void oled_update_display(uint8_t display_id);

/**
 * @brief Clear the display
 * 
 * @param display_id Display ID (OLED_DISPLAY_1 or OLED_DISPLAY_2)
 */
void oled_clear(uint8_t display_id);

/**
 * @brief Display custom text at specified position
 * 
 * @param display_id Display ID (OLED_DISPLAY_1 or OLED_DISPLAY_2)
 * @param text Text to display
 * @param x X coordinate
 * @param y Y coordinate
 * @param size Text size (1-3)
 */
void oled_show_text(uint8_t display_id, const char *text, int16_t x, int16_t y, uint8_t size);

/**
 * @brief Update cached audio levels for display 1
 *
 * @param left_rms RMS level for left channel (0.0 - 1.0)
 * @param right_rms RMS level for right channel (0.0 - 1.0)
 * @param peak Peak level across channels (0.0 - 1.0)
 */
void oled_set_audio_levels(float left_rms, float right_rms, float peak);

/**
 * @brief Update cached table data for display 1 (array1)
 *
 * @param data Pointer to table data (0.0 - 1.0)
 * @param length Number of samples in data
 */
void oled_set_table_data(const float *data, uint32_t length);

#ifdef __cplusplus
}
#endif

#endif // OLED_DISPLAY_H
