#include "display.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_heap_caps.h"
#include "esp_lcd_gc9a01.h"
#include "esp_log.h"

static const char *TAG = "display";

esp_err_t display_init(esp_lcd_panel_io_handle_t *io_handle, esp_lcd_panel_handle_t *panel_handle)
{
    ESP_LOGI(TAG, "Initialize SPI bus");
    const spi_bus_config_t bus_config = {
        .sclk_io_num = PIN_LCD_CLK,
        .mosi_io_num = PIN_LCD_MOSI,
        .miso_io_num = GPIO_NUM_NC,
        .quadwp_io_num = GPIO_NUM_NC,
        .quadhd_io_num = GPIO_NUM_NC,
        .max_transfer_sz = LCD_H_RES * 80 * sizeof(uint16_t),
    };
    ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST, &bus_config, SPI_DMA_CH_AUTO));

    ESP_LOGI(TAG, "Install panel IO");
    esp_lcd_panel_io_handle_t io = NULL;
    const esp_lcd_panel_io_spi_config_t io_config = {
        .dc_gpio_num = PIN_LCD_DC,
        .cs_gpio_num = PIN_LCD_CS,
        .pclk_hz = LCD_PIXEL_CLOCK_HZ,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
        .spi_mode = 0,
        .trans_queue_depth = 10,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST, &io_config, &io));

    ESP_LOGI(TAG, "Install GC9A01 panel driver (HSD 1.28 vendor init)");
    esp_lcd_panel_handle_t panel = NULL;

    size_t init_cmds_size = 0;
    const gc9a01_lcd_init_cmd_t *init_cmds = display_get_vendor_init_cmds(&init_cmds_size);
    const gc9a01_vendor_config_t vendor_config = {
        .init_cmds = init_cmds,
        .init_cmds_size = init_cmds_size,
    };

    const esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = PIN_LCD_RST,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
        .bits_per_pixel = 16,
        .vendor_config = &vendor_config,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_gc9a01(io, &panel_config, &panel));
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel));
    vTaskDelay(pdMS_TO_TICKS(120));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel));

    *io_handle = io;
    *panel_handle = panel;
    return ESP_OK;
}

void display_set_backlight(bool on)
{
    static bool gpio_ready = false;

    if (!gpio_ready) {
        const gpio_config_t bl_gpio_config = {
            .mode = GPIO_MODE_OUTPUT,
            .pin_bit_mask = 1ULL << PIN_LCD_BL,
        };
        ESP_ERROR_CHECK(gpio_config(&bl_gpio_config));
        gpio_ready = true;
    }

    const int level = on ? LCD_BL_ON_LEVEL : !LCD_BL_ON_LEVEL;
    gpio_set_level(PIN_LCD_BL, level);
    ESP_LOGI(TAG, "Backlight %s, GPIO%d=%d", on ? "ON" : "OFF", PIN_LCD_BL, level);
}

void display_fill_color(esp_lcd_panel_handle_t panel, uint16_t color_rgb565)
{
    const size_t line_pixels = LCD_H_RES;
    uint16_t *line_buf = heap_caps_malloc(line_pixels * sizeof(uint16_t), MALLOC_CAP_DMA);
    if (line_buf == NULL) {
        ESP_LOGE(TAG, "Failed to allocate line buffer for color fill");
        return;
    }

    for (size_t i = 0; i < line_pixels; i++) {
        line_buf[i] = color_rgb565;
    }

    for (int y = 0; y < LCD_V_RES; y++) {
        ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(panel, 0, y, LCD_H_RES, y + 1, line_buf));
    }

    heap_caps_free(line_buf);
}
