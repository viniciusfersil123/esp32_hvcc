/**
 * @file oled_display.c
 * @brief OLED Display Implementation for SSD1306 using ESP-IDF
 */

#include "oled_display.h"
#include <string.h>
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_random.h"

static const char *TAG = "OLED";

// SPI device handle
static spi_device_handle_t spi_device;
static bool is_initialized = false;
static uint32_t update_counter = 0;

// Display buffer (128x64 pixels, 1 bit per pixel = 1024 bytes)
static uint8_t display_buffer[OLED_WIDTH * OLED_HEIGHT / 8];

// 5x7 font (ASCII 32-127)
static const uint8_t font_5x7[][5] = {
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 32 (space)
    {0x00, 0x00, 0x5F, 0x00, 0x00}, // 33 !
    {0x00, 0x07, 0x00, 0x07, 0x00}, // 34 "
    {0x14, 0x7F, 0x14, 0x7F, 0x14}, // 35 #
    {0x24, 0x2A, 0x7F, 0x2A, 0x12}, // 36 $
    {0x23, 0x13, 0x08, 0x64, 0x62}, // 37 %
    {0x36, 0x49, 0x55, 0x22, 0x50}, // 38 &
    {0x00, 0x05, 0x03, 0x00, 0x00}, // 39 '
    {0x00, 0x1C, 0x22, 0x41, 0x00}, // 40 (
    {0x00, 0x41, 0x22, 0x1C, 0x00}, // 41 )
    {0x14, 0x08, 0x3E, 0x08, 0x14}, // 42 *
    {0x08, 0x08, 0x3E, 0x08, 0x08}, // 43 +
    {0x00, 0x50, 0x30, 0x00, 0x00}, // 44 ,
    {0x08, 0x08, 0x08, 0x08, 0x08}, // 45 -
    {0x00, 0x60, 0x60, 0x00, 0x00}, // 46 .
    {0x20, 0x10, 0x08, 0x04, 0x02}, // 47 /
    {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 48 0
    {0x00, 0x42, 0x7F, 0x40, 0x00}, // 49 1
    {0x42, 0x61, 0x51, 0x49, 0x46}, // 50 2
    {0x21, 0x41, 0x45, 0x4B, 0x31}, // 51 3
    {0x18, 0x14, 0x12, 0x7F, 0x10}, // 52 4
    {0x27, 0x45, 0x45, 0x45, 0x39}, // 53 5
    {0x3C, 0x4A, 0x49, 0x49, 0x30}, // 54 6
    {0x01, 0x71, 0x09, 0x05, 0x03}, // 55 7
    {0x36, 0x49, 0x49, 0x49, 0x36}, // 56 8
    {0x06, 0x49, 0x49, 0x29, 0x1E}, // 57 9
    {0x00, 0x36, 0x36, 0x00, 0x00}, // 58 :
    {0x00, 0x56, 0x36, 0x00, 0x00}, // 59 ;
    {0x08, 0x14, 0x22, 0x41, 0x00}, // 60 <
    {0x14, 0x14, 0x14, 0x14, 0x14}, // 61 =
    {0x00, 0x41, 0x22, 0x14, 0x08}, // 62 >
    {0x02, 0x01, 0x51, 0x09, 0x06}, // 63 ?
    {0x32, 0x49, 0x79, 0x41, 0x3E}, // 64 @
    {0x7E, 0x11, 0x11, 0x11, 0x7E}, // 65 A
    {0x7F, 0x49, 0x49, 0x49, 0x36}, // 66 B
    {0x3E, 0x41, 0x41, 0x41, 0x22}, // 67 C
    {0x7F, 0x41, 0x41, 0x22, 0x1C}, // 68 D
    {0x7F, 0x49, 0x49, 0x49, 0x41}, // 69 E
    {0x7F, 0x09, 0x09, 0x09, 0x01}, // 70 F
    {0x3E, 0x41, 0x49, 0x49, 0x7A}, // 71 G
    {0x7F, 0x08, 0x08, 0x08, 0x7F}, // 72 H
    {0x00, 0x41, 0x7F, 0x41, 0x00}, // 73 I
    {0x20, 0x40, 0x41, 0x3F, 0x01}, // 74 J
    {0x7F, 0x08, 0x14, 0x22, 0x41}, // 75 K
    {0x7F, 0x40, 0x40, 0x40, 0x40}, // 76 L
    {0x7F, 0x02, 0x0C, 0x02, 0x7F}, // 77 M
    {0x7F, 0x04, 0x08, 0x10, 0x7F}, // 78 N
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, // 79 O
    {0x7F, 0x09, 0x09, 0x09, 0x06}, // 80 P
    {0x3E, 0x41, 0x51, 0x21, 0x5E}, // 81 Q
    {0x7F, 0x09, 0x19, 0x29, 0x46}, // 82 R
    {0x46, 0x49, 0x49, 0x49, 0x31}, // 83 S
    {0x01, 0x01, 0x7F, 0x01, 0x01}, // 84 T
    {0x3F, 0x40, 0x40, 0x40, 0x3F}, // 85 U
    {0x1F, 0x20, 0x40, 0x20, 0x1F}, // 86 V
    {0x3F, 0x40, 0x38, 0x40, 0x3F}, // 87 W
    {0x63, 0x14, 0x08, 0x14, 0x63}, // 88 X
    {0x07, 0x08, 0x70, 0x08, 0x07}, // 89 Y
    {0x61, 0x51, 0x49, 0x45, 0x43}, // 90 Z
    {0x00, 0x7F, 0x41, 0x41, 0x00}, // 91 [
    {0x02, 0x04, 0x08, 0x10, 0x20}, // 92 backslash
    {0x00, 0x41, 0x41, 0x7F, 0x00}, // 93 ]
    {0x04, 0x02, 0x01, 0x02, 0x04}, // 94 ^
    {0x40, 0x40, 0x40, 0x40, 0x40}, // 95 _
    {0x00, 0x01, 0x02, 0x04, 0x00}, // 96 `
    {0x20, 0x54, 0x54, 0x54, 0x78}, // 97 a
    {0x7F, 0x48, 0x44, 0x44, 0x38}, // 98 b
    {0x38, 0x44, 0x44, 0x44, 0x20}, // 99 c
    {0x38, 0x44, 0x44, 0x48, 0x7F}, // 100 d
    {0x38, 0x54, 0x54, 0x54, 0x18}, // 101 e
    {0x08, 0x7E, 0x09, 0x01, 0x02}, // 102 f
    {0x0C, 0x52, 0x52, 0x52, 0x3E}, // 103 g
    {0x7F, 0x08, 0x04, 0x04, 0x78}, // 104 h
    {0x00, 0x44, 0x7D, 0x40, 0x00}, // 105 i
    {0x20, 0x40, 0x44, 0x3D, 0x00}, // 106 j
    {0x7F, 0x10, 0x28, 0x44, 0x00}, // 107 k
    {0x00, 0x41, 0x7F, 0x40, 0x00}, // 108 l
    {0x7C, 0x04, 0x18, 0x04, 0x78}, // 109 m
    {0x7C, 0x08, 0x04, 0x04, 0x78}, // 110 n
    {0x38, 0x44, 0x44, 0x44, 0x38}, // 111 o
    {0x7C, 0x14, 0x14, 0x14, 0x08}, // 112 p
    {0x08, 0x14, 0x14, 0x18, 0x7C}, // 113 q
    {0x7C, 0x08, 0x04, 0x04, 0x08}, // 114 r
    {0x48, 0x54, 0x54, 0x54, 0x20}, // 115 s
    {0x04, 0x3F, 0x44, 0x40, 0x20}, // 116 t
    {0x3C, 0x40, 0x40, 0x20, 0x7C}, // 117 u
    {0x1C, 0x20, 0x40, 0x20, 0x1C}, // 118 v
    {0x3C, 0x40, 0x30, 0x40, 0x3C}, // 119 w
    {0x44, 0x28, 0x10, 0x28, 0x44}, // 120 x
    {0x0C, 0x50, 0x50, 0x50, 0x3C}, // 121 y
    {0x44, 0x64, 0x54, 0x4C, 0x44}, // 122 z
    {0x00, 0x08, 0x36, 0x41, 0x00}, // 123 {
    {0x00, 0x00, 0x7F, 0x00, 0x00}, // 124 |
    {0x00, 0x41, 0x36, 0x08, 0x00}, // 125 }
    {0x10, 0x08, 0x08, 0x10, 0x08}, // 126 ~
};

// SSD1306 Commands
#define SSD1306_SETCONTRAST         0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON        0xA5
#define SSD1306_NORMALDISPLAY       0xA6
#define SSD1306_INVERTDISPLAY       0xA7
#define SSD1306_DISPLAYOFF          0xAE
#define SSD1306_DISPLAYON           0xAF
#define SSD1306_SETDISPLAYOFFSET    0xD3
#define SSD1306_SETCOMPINS          0xDA
#define SSD1306_SETVCOMDETECT       0xDB
#define SSD1306_SETDISPLAYCLOCKDIV  0xD5
#define SSD1306_SETPRECHARGE        0xD9
#define SSD1306_SETMULTIPLEX        0xA8
#define SSD1306_SETLOWCOLUMN        0x00
#define SSD1306_SETHIGHCOLUMN       0x10
#define SSD1306_SETSTARTLINE        0x40
#define SSD1306_MEMORYMODE          0x20
#define SSD1306_COLUMNADDR          0x21
#define SSD1306_PAGEADDR            0x22
#define SSD1306_COMSCANINC          0xC0
#define SSD1306_COMSCANDEC          0xC8
#define SSD1306_SEGREMAP            0xA0
#define SSD1306_CHARGEPUMP          0x8D

static void ssd1306_write_command(uint8_t cmd) {
    gpio_set_level((gpio_num_t)OLED_PIN_DC, 0);  // Command mode
    spi_transaction_t t = {};
    t.length = 8;
    t.tx_buffer = &cmd;
    spi_device_polling_transmit(spi_device, &t);
}

static void ssd1306_write_data(const uint8_t *data, size_t len) {
    gpio_set_level((gpio_num_t)OLED_PIN_DC, 1);  // Data mode
    spi_transaction_t t = {};
    t.length = len * 8;
    t.tx_buffer = data;
    spi_device_polling_transmit(spi_device, &t);
}

bool oled_init(void) {
    ESP_LOGI(TAG, "Initializing OLED display...");
    ESP_LOGI(TAG, "Pins - MOSI:%d CLK:%d DC:%d CS:%d RST:%d", 
             OLED_PIN_MOSI, OLED_PIN_CLK, OLED_PIN_DC, OLED_PIN_CS, OLED_PIN_RESET);
    
    // Configure DC and RESET pins
    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = (1ULL << OLED_PIN_DC) | (1ULL << OLED_PIN_RESET);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&io_conf);
    
    // Reset display
    gpio_set_level((gpio_num_t)OLED_PIN_RESET, 0);
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level((gpio_num_t)OLED_PIN_RESET, 1);
    vTaskDelay(pdMS_TO_TICKS(10));
    
    // Configure SPI bus
    spi_bus_config_t bus_cfg = {};
    bus_cfg.mosi_io_num = OLED_PIN_MOSI;
    bus_cfg.miso_io_num = -1;
    bus_cfg.sclk_io_num = OLED_PIN_CLK;
    bus_cfg.quadwp_io_num = -1;
    bus_cfg.quadhd_io_num = -1;
    bus_cfg.max_transfer_sz = OLED_WIDTH * OLED_HEIGHT / 8;
    
    esp_err_t ret = spi_bus_initialize(SPI2_HOST, &bus_cfg, SPI_DMA_CH_AUTO);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize SPI bus: %s", esp_err_to_name(ret));
        return false;
    }
    
    // Configure SPI device
    spi_device_interface_config_t dev_cfg = {};
    dev_cfg.clock_speed_hz = 10 * 1000 * 1000;  // 10 MHz
    dev_cfg.mode = 0;
    dev_cfg.spics_io_num = OLED_PIN_CS;
    dev_cfg.queue_size = 1;
    
    ret = spi_bus_add_device(SPI2_HOST, &dev_cfg, &spi_device);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to add SPI device: %s", esp_err_to_name(ret));
        return false;
    }
    
    // Initialize SSD1306
    ssd1306_write_command(SSD1306_DISPLAYOFF);
    ssd1306_write_command(SSD1306_SETDISPLAYCLOCKDIV);
    ssd1306_write_command(0x80);
    ssd1306_write_command(SSD1306_SETMULTIPLEX);
    ssd1306_write_command(0x3F);
    ssd1306_write_command(SSD1306_SETDISPLAYOFFSET);
    ssd1306_write_command(0x00);
    ssd1306_write_command(SSD1306_SETSTARTLINE | 0x00);
    ssd1306_write_command(SSD1306_CHARGEPUMP);
    ssd1306_write_command(0x14);
    ssd1306_write_command(SSD1306_MEMORYMODE);
    ssd1306_write_command(0x00);
    ssd1306_write_command(SSD1306_SEGREMAP | 0x01);
    ssd1306_write_command(SSD1306_COMSCANDEC);
    ssd1306_write_command(SSD1306_SETCOMPINS);
    ssd1306_write_command(0x12);
    ssd1306_write_command(SSD1306_SETCONTRAST);
    ssd1306_write_command(0xCF);
    ssd1306_write_command(SSD1306_SETPRECHARGE);
    ssd1306_write_command(0xF1);
    ssd1306_write_command(SSD1306_SETVCOMDETECT);
    ssd1306_write_command(0x40);
    ssd1306_write_command(SSD1306_DISPLAYALLON_RESUME);
    ssd1306_write_command(SSD1306_NORMALDISPLAY);
    ssd1306_write_command(SSD1306_DISPLAYON);
    
    ESP_LOGI(TAG, "OLED initialized successfully!");
    
    // Clear and show initial message
    memset(display_buffer, 0, sizeof(display_buffer));
    oled_clear();
    
    is_initialized = true;
    return true;
}

void oled_clear(void) {
    if (!is_initialized) return;
    
    memset(display_buffer, 0, sizeof(display_buffer));
    
    ssd1306_write_command(SSD1306_COLUMNADDR);
    ssd1306_write_command(0);
    ssd1306_write_command(OLED_WIDTH - 1);
    ssd1306_write_command(SSD1306_PAGEADDR);
    ssd1306_write_command(0);
    ssd1306_write_command(7);
    
    ssd1306_write_data(display_buffer, sizeof(display_buffer));
}

static void oled_draw_char(char c, int16_t x, int16_t y) {
    if (c < 32 || c > 126) c = 32;  // Limit to printable ASCII
    int idx = c - 32;
    
    for (int col = 0; col < 5; col++) {
        uint8_t line = font_5x7[idx][col];
        for (int row = 0; row < 8; row++) {
            if (line & (1 << row)) {
                int px = x + col;
                int py = y + row;
                if (px >= 0 && px < OLED_WIDTH && py >= 0 && py < OLED_HEIGHT) {
                    display_buffer[px + (py / 8) * OLED_WIDTH] |= (1 << (py % 8));
                }
            }
        }
    }
}

void oled_show_text(const char *text, int16_t x, int16_t y, uint8_t size) {
    if (!is_initialized) return;
    
    int16_t cursor_x = x;
    while (*text) {
        oled_draw_char(*text, cursor_x, y);
        cursor_x += 6;  // 5 pixels + 1 space
        text++;
    }
}

void oled_update_display(void) {
    if (!is_initialized) return;
    
    update_counter++;
    
    // Clear buffer
    memset(display_buffer, 0, sizeof(display_buffer));
    
    // Draw text
    oled_show_text("ESP32 HVCC", 10, 0, 1);
    oled_show_text("Hello World!", 5, 20, 1);
    
    char info[32];
    snprintf(info, sizeof(info), "Count: %lu", update_counter);
    oled_show_text(info, 5, 40, 1);
    
    uint32_t random_val = esp_random() % 1000;
    snprintf(info, sizeof(info), "Random: %lu", random_val);
    oled_show_text(info, 5, 50, 1);
    
    // Send buffer to display
    ssd1306_write_command(SSD1306_COLUMNADDR);
    ssd1306_write_command(0);
    ssd1306_write_command(OLED_WIDTH - 1);
    ssd1306_write_command(SSD1306_PAGEADDR);
    ssd1306_write_command(0);
    ssd1306_write_command(7);
    
    ssd1306_write_data(display_buffer, sizeof(display_buffer));
}
