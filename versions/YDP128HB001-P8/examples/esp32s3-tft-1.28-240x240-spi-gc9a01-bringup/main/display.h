#pragma once

#include <stddef.h>

#include "esp_err.h"
#include "esp_lcd_gc9a01.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"

#define LCD_HOST                SPI2_HOST

#define LCD_H_RES               240
#define LCD_V_RES               240

#define PIN_LCD_BL              9
#define PIN_LCD_RST             10
#define PIN_LCD_DC              11
#define PIN_LCD_CS              12
#define PIN_LCD_CLK             13
#define PIN_LCD_MOSI            14

#define LCD_PIXEL_CLOCK_HZ      (40 * 1000 * 1000)
#define LCD_DRAW_BUF_LINES      20

/* 多数 1.28" GC9A01 模组背光为低电平有效；若背光常亮但无画面，改为 1 */
#define LCD_BL_ON_LEVEL         0

esp_err_t display_init(esp_lcd_panel_io_handle_t *io_handle, esp_lcd_panel_handle_t *panel_handle);
void display_set_backlight(bool on);
void display_fill_color(esp_lcd_panel_handle_t panel, uint16_t color_rgb565);
const gc9a01_lcd_init_cmd_t *display_get_vendor_init_cmds(size_t *out_size);
