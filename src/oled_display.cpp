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

// SPI device handles for both displays
static spi_device_handle_t spi_devices[OLED_MAX_DISPLAYS] = {NULL, NULL};

// Display buffers (one for each display)
static uint8_t display_buffers[OLED_MAX_DISPLAYS][OLED_WIDTH * OLED_HEIGHT / 8];

// Configuration and state
static oled_config_t active_config;
static bool is_initialized = false;
static uint32_t update_counters[OLED_MAX_DISPLAYS] = {0, 0};
static float audio_rms_left = 0.0f;
static float audio_rms_right = 0.0f;
static float audio_peak = 0.0f;

// Table cache - increased to handle large tables (e.g., 259 samples)
#define TABLE_CACHE_MAX 512
static float table_cache[TABLE_CACHE_MAX] = {0.0f};
static uint32_t table_cache_len = 0;
static float table_min = 0.0f;
static float table_max = 1.0f;
static uint8_t current_table_display = 0;  // Which display is currently using the table cache

// Get appropriate buffer for display ID
static inline uint8_t *get_display_buffer(uint8_t display_id) {
    return (display_id < active_config.num_displays) ? display_buffers[display_id] : NULL;
}

// Get appropriate device handle for display ID
static inline spi_device_handle_t get_spi_device(uint8_t display_id) {
    return (display_id < active_config.num_displays) ? spi_devices[display_id] : NULL;
}

static inline void oled_set_pixel(uint8_t *buffer, int x, int y, bool on) {
    if (x < 0 || x >= OLED_WIDTH || y < 0 || y >= OLED_HEIGHT) {
        return;
    }
    if (on) {
        buffer[x + (y / 8) * OLED_WIDTH] |= (1 << (y % 8));
    } else {
        buffer[x + (y / 8) * OLED_WIDTH] &= ~(1 << (y % 8));
    }
}

static void oled_draw_filled_rect(uint8_t *buffer, int x, int y, int w, int h) {
    for (int yy = y; yy < y + h; yy++) {
        for (int xx = x; xx < x + w; xx++) {
            oled_set_pixel(buffer, xx, yy, true);
        }
    }
}

// Bresenham's line drawing algorithm
static void oled_draw_line(uint8_t *buffer, int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    
    while (true) {
        oled_set_pixel(buffer, x0, y0, true);
        
        if (x0 == x1 && y0 == y1) break;
        
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

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

static void ssd1306_write_command(spi_device_handle_t device, uint8_t cmd) {
    gpio_set_level((gpio_num_t)active_config.dc_pin, 0);  // Command mode
    spi_transaction_t t = {};
    t.length = 8;
    t.tx_buffer = &cmd;
    spi_device_polling_transmit(device, &t);
}

static void ssd1306_write_data(spi_device_handle_t device, const uint8_t *data, size_t len) {
    gpio_set_level((gpio_num_t)active_config.dc_pin, 1);  // Data mode
    spi_transaction_t t = {};
    t.length = len * 8;
    t.tx_buffer = data;
    spi_device_polling_transmit(device, &t);
}

static void ssd1306_init_display(spi_device_handle_t device) {
    ssd1306_write_command(device, SSD1306_DISPLAYOFF);
    ssd1306_write_command(device, SSD1306_SETDISPLAYCLOCKDIV);
    ssd1306_write_command(device, 0x80);
    ssd1306_write_command(device, SSD1306_SETMULTIPLEX);
    ssd1306_write_command(device, 0x3F);
    ssd1306_write_command(device, SSD1306_SETDISPLAYOFFSET);
    ssd1306_write_command(device, 0x00);
    ssd1306_write_command(device, SSD1306_SETSTARTLINE | 0x00);
    ssd1306_write_command(device, SSD1306_CHARGEPUMP);
    ssd1306_write_command(device, 0x14);
    ssd1306_write_command(device, SSD1306_MEMORYMODE);
    ssd1306_write_command(device, 0x00);
    ssd1306_write_command(device, SSD1306_SEGREMAP | 0x01);
    ssd1306_write_command(device, SSD1306_COMSCANDEC);
    ssd1306_write_command(device, SSD1306_SETCOMPINS);
    ssd1306_write_command(device, 0x12);
    ssd1306_write_command(device, SSD1306_SETCONTRAST);
    ssd1306_write_command(device, 0xCF);
    ssd1306_write_command(device, SSD1306_SETPRECHARGE);
    ssd1306_write_command(device, 0xF1);
    ssd1306_write_command(device, SSD1306_SETVCOMDETECT);
    ssd1306_write_command(device, 0x40);
    ssd1306_write_command(device, SSD1306_DISPLAYALLON_RESUME);
    ssd1306_write_command(device, SSD1306_NORMALDISPLAY);
    ssd1306_write_command(device, SSD1306_DISPLAYON);
}

bool oled_init(const oled_config_t *config) {
    if (!config || config->num_displays == 0 || config->num_displays > OLED_MAX_DISPLAYS) {
        ESP_LOGE(TAG, "Invalid configuration");
        return false;
    }
    
    // Store configuration
    memcpy(&active_config, config, sizeof(oled_config_t));
    
    ESP_LOGI(TAG, "Initializing %d OLED display(s)...", config->num_displays);
    ESP_LOGI(TAG, "Pins - MOSI:%d CLK:%d DC:%d RST:%d", 
             config->mosi_pin, config->clk_pin, config->dc_pin, config->rst_pin);
    
    // Configure DC and RESET pins
    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = (1ULL << config->dc_pin) | (1ULL << config->rst_pin);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&io_conf);
    
    // Reset displays
    gpio_set_level((gpio_num_t)config->rst_pin, 0);
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level((gpio_num_t)config->rst_pin, 1);
    vTaskDelay(pdMS_TO_TICKS(10));
    
    // Configure SPI bus (shared)
    spi_bus_config_t bus_cfg = {};
    bus_cfg.mosi_io_num = config->mosi_pin;
    bus_cfg.miso_io_num = -1;
    bus_cfg.sclk_io_num = config->clk_pin;
    bus_cfg.quadwp_io_num = -1;
    bus_cfg.quadhd_io_num = -1;
    bus_cfg.max_transfer_sz = OLED_WIDTH * OLED_HEIGHT / 8;
    
    esp_err_t ret = spi_bus_initialize(SPI2_HOST, &bus_cfg, SPI_DMA_CH_AUTO);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize SPI bus: %s", esp_err_to_name(ret));
        return false;
    }
    
    // Initialize each display
    for (uint8_t i = 0; i < config->num_displays; i++) {
        const oled_display_config_t *disp = &config->displays[i];
        
        ESP_LOGI(TAG, "Display %d: CS=%d, Table='%s'", 
                 disp->id, disp->cs_pin, 
                 disp->table_name[0] ? disp->table_name : "none");
        
        // Configure SPI device
        spi_device_interface_config_t dev_cfg = {};
        dev_cfg.clock_speed_hz = 10 * 1000 * 1000;  // 10 MHz
        dev_cfg.mode = 0;
        dev_cfg.spics_io_num = disp->cs_pin;
        dev_cfg.queue_size = 1;
        
        ret = spi_bus_add_device(SPI2_HOST, &dev_cfg, &spi_devices[i]);
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "Failed to add SPI device %d: %s", i, esp_err_to_name(ret));
            return false;
        }
        
        // Initialize SSD1306
        ESP_LOGI(TAG, "Initializing Display %d...", disp->id);
        ssd1306_init_display(spi_devices[i]);
        
        // Clear display
        memset(display_buffers[i], 0, sizeof(display_buffers[i]));
        oled_clear(i);
    }
    
    ESP_LOGI(TAG, "All OLED displays initialized successfully!");
    
    is_initialized = true;
    return true;
}

void oled_clear(uint8_t display_id) {
    if (!is_initialized) return;
    
    uint8_t *buffer = get_display_buffer(display_id);
    spi_device_handle_t device = get_spi_device(display_id);
    
    memset(buffer, 0, OLED_WIDTH * OLED_HEIGHT / 8);
    
    ssd1306_write_command(device, SSD1306_COLUMNADDR);
    ssd1306_write_command(device, 0);
    ssd1306_write_command(device, OLED_WIDTH - 1);
    ssd1306_write_command(device, SSD1306_PAGEADDR);
    ssd1306_write_command(device, 0);
    ssd1306_write_command(device, 7);
    
    ssd1306_write_data(device, buffer, OLED_WIDTH * OLED_HEIGHT / 8);
}

static void oled_draw_char(uint8_t display_id, char c, int16_t x, int16_t y) {
    if (c < 32 || c > 126) c = 32;  // Limit to printable ASCII
    int idx = c - 32;
    uint8_t *buffer = get_display_buffer(display_id);
    
    for (int col = 0; col < 5; col++) {
        uint8_t line = font_5x7[idx][col];
        for (int row = 0; row < 8; row++) {
            if (line & (1 << row)) {
                int px = x + col;
                int py = y + row;
                if (px >= 0 && px < OLED_WIDTH && py >= 0 && py < OLED_HEIGHT) {
                    buffer[px + (py / 8) * OLED_WIDTH] |= (1 << (py % 8));
                }
            }
        }
    }
}

void oled_show_text(uint8_t display_id, const char *text, int16_t x, int16_t y, uint8_t size) {
    if (!is_initialized) return;
    
    int16_t cursor_x = x;
    while (*text) {
        oled_draw_char(display_id, *text, cursor_x, y);
        cursor_x += 6;  // 5 pixels + 1 space
        text++;
    }
}

void oled_set_audio_levels(float left_rms, float right_rms, float peak) {
    if (left_rms < 0.0f) left_rms = 0.0f;
    if (right_rms < 0.0f) right_rms = 0.0f;
    if (peak < 0.0f) peak = 0.0f;
    if (left_rms > 1.0f) left_rms = 1.0f;
    if (right_rms > 1.0f) right_rms = 1.0f;
    if (peak > 1.0f) peak = 1.0f;

    audio_rms_left = left_rms;
    audio_rms_right = right_rms;
    audio_peak = peak;
}

void oled_set_table_data(const float *data, uint32_t length) {
    if (!data || length == 0) {
        table_cache_len = 0;
        return;
    }

    // Store up to TABLE_CACHE_MAX samples
    uint32_t copy_len = (length > TABLE_CACHE_MAX) ? TABLE_CACHE_MAX : length;
    
    // Auto-scale: find min/max in the data
    float min_val = data[0];
    float max_val = data[0];
    for (uint32_t i = 0; i < copy_len; i++) {
        if (data[i] < min_val) min_val = data[i];
        if (data[i] > max_val) max_val = data[i];
    }
    table_min = min_val;
    table_max = max_val;
    
    // Avoid division by zero
    if (table_max <= table_min) {
        table_max = table_min + 1.0f;
    }
    
    // Store raw data without clamping
    for (uint32_t i = 0; i < copy_len; i++) {
        table_cache[i] = data[i];
    }
    for (uint32_t i = copy_len; i < TABLE_CACHE_MAX; i++) {
        table_cache[i] = 0.0f;
    }
    table_cache_len = copy_len;
}

void oled_update_display(uint8_t display_id) {
    if (!is_initialized || display_id >= active_config.num_displays) return;
    
    uint8_t *buffer = get_display_buffer(display_id);
    spi_device_handle_t device = get_spi_device(display_id);
    
    update_counters[display_id]++;
    
    current_table_display = display_id;
    
    // Clear buffer
    memset(buffer, 0, OLED_WIDTH * OLED_HEIGHT / 8);
    
    const oled_display_config_t *disp_cfg = &active_config.displays[display_id];
    
    // Check if this display has a table assigned
    if (disp_cfg->table_name[0] != '\0') {
        // Table waveform view - draw connected line segments
        // Map table_min..table_max to bottom..top of display
        int base_y = OLED_HEIGHT - 1;
        int prev_x = -1, prev_y = -1;
        
        // Handle horizontal scaling: fit all table_cache_len samples into OLED_WIDTH pixels
        for (int x = 0; x < (int)OLED_WIDTH; x++) {
            float v = 0.0f;
            
            if (table_cache_len > 0) {
                if (table_cache_len <= OLED_WIDTH) {
                    // Less data than pixels: direct mapping
                    if (x < (int)table_cache_len) {
                        v = table_cache[x];
                    }
                } else {
                    // More data than pixels: use linear interpolation to resample
                    // Map pixel x to sample position in the original data
                    float sample_pos = (float)x * (table_cache_len - 1) / (OLED_WIDTH - 1);
                    int idx0 = (int)sample_pos;
                    int idx1 = idx0 + 1;
                    float frac = sample_pos - idx0;
                    
                    if (idx1 >= (int)table_cache_len) {
                        idx1 = table_cache_len - 1;
                        frac = 0.0f;
                    }
                    
                    // Linear interpolation between idx0 and idx1
                    float v0 = table_cache[idx0];
                    float v1 = table_cache[idx1];
                    v = v0 + frac * (v1 - v0);
                }
            }
            
            // Scale value from [table_min, table_max] to [0, 1]
            float scaled_v = (v - table_min) / (table_max - table_min);
            // Clamp to display range
            if (scaled_v < 0.0f) scaled_v = 0.0f;
            if (scaled_v > 1.0f) scaled_v = 1.0f;
            // Map 0.0->1.0 to display height (0 at bottom, 63 at top)
            int y = base_y - (int)(scaled_v * (OLED_HEIGHT - 1));
            if (y < 0) y = 0;
            if (y > base_y) y = base_y;
            
            // Draw line from previous point to current point
            if (prev_x >= 0) {
                oled_draw_line(buffer, prev_x, prev_y, x, y);
            } else {
                oled_set_pixel(buffer, x, y, true);
            }
            
            prev_x = x;
            prev_y = y;
        }
    } else {
        // Text info display
        char line[32];
        snprintf(line, sizeof(line), "Display %d", disp_cfg->id);
        oled_show_text(display_id, line, 10, 0, 1);
        
        oled_show_text(display_id, "Ai de mim!", 5, 20, 1);

        snprintf(line, sizeof(line), "Count: %lu", update_counters[display_id]);
        oled_show_text(display_id, line, 5, 40, 1);

        uint32_t random_val = esp_random() % 1000;
        snprintf(line, sizeof(line), "Rnd: %lu", random_val);
        oled_show_text(display_id, line, 5, 50, 1);
    }
    
    // Send buffer to display
    ssd1306_write_command(device, SSD1306_COLUMNADDR);
    ssd1306_write_command(device, 0);
    ssd1306_write_command(device, OLED_WIDTH - 1);
    ssd1306_write_command(device, SSD1306_PAGEADDR);
    ssd1306_write_command(device, 0);
    ssd1306_write_command(device, 7);
    
    ssd1306_write_data(device, buffer, OLED_WIDTH * OLED_HEIGHT / 8);
}
