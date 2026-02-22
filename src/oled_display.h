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

// SPI Pin Configuration for OLED
#define OLED_PIN_MOSI   23
#define OLED_PIN_CLK    18
#define OLED_PIN_DC     16
#define OLED_PIN_CS     5
#define OLED_PIN_RESET  17

// Display dimensions
#define OLED_WIDTH      128
#define OLED_HEIGHT     64

/**
 * @brief Initialize OLED display
 * 
 * Sets up SPI communication and initializes the SSD1306 display
 * 
 * @return true on success, false on failure
 */
bool oled_init(void);

/**
 * @brief Update display with Hello World and random info
 * 
 * Shows a simple hello world message and some random system information
 */
void oled_update_display(void);

/**
 * @brief Clear the display
 */
void oled_clear(void);

/**
 * @brief Display custom text at specified position
 * 
 * @param text Text to display
 * @param x X coordinate
 * @param y Y coordinate
 * @param size Text size (1-3)
 */
void oled_show_text(const char *text, int16_t x, int16_t y, uint8_t size);

#ifdef __cplusplus
}
#endif

#endif // OLED_DISPLAY_H
