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

// SPI Pin Configuration for OLED (shared SPI bus)
#define OLED_PIN_MOSI   23
#define OLED_PIN_CLK    18
#define OLED_PIN_DC     16
#define OLED_PIN_RESET  17
#define OLED_PIN_CS1    5
#define OLED_PIN_CS2    15

// Display IDs
#define OLED_DISPLAY_1  0
#define OLED_DISPLAY_2  1

// Display dimensions
#define OLED_WIDTH      128
#define OLED_HEIGHT     64

/**
 * @brief Initialize OLED displays (1 or 2 displays on shared SPI bus)
 * 
 * Sets up SPI communication and initializes SSD1306 display(s)
 * 
 * @return true on success, false on failure
 */
bool oled_init(void);

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

#ifdef __cplusplus
}
#endif

#endif // OLED_DISPLAY_H
