/*
 * SPDX-FileCopyrightText: Copyright 2026 OSPTEK
 * SPDX-License-Identifier: CC-BY-4.0
 *
 * https://github.com/osptek
 */

#include "display.h"
#include "ui_anim.h"

#include "esp_log.h"
#include "esp_lvgl_port.h"

static const char *TAG = "main";

void app_main(void)
{
    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_handle_t panel_handle = NULL;

    display_set_backlight(false);
    ESP_ERROR_CHECK(display_init(&io_handle, &panel_handle));
    display_set_backlight(true);

    ESP_LOGI(TAG, "Initialize LVGL port");
    const lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();
    ESP_ERROR_CHECK(lvgl_port_init(&lvgl_cfg));

    const lvgl_port_display_cfg_t disp_cfg = {
        .io_handle = io_handle,
        .panel_handle = panel_handle,
        .buffer_size = LCD_H_RES * LCD_DRAW_BUF_LINES,
        .double_buffer = true,
        .hres = LCD_H_RES,
        .vres = LCD_V_RES,
        .monochrome = false,
        .color_format = LV_COLOR_FORMAT_RGB565,
        .rotation = {
            .swap_xy = false,
            .mirror_x = false,
            .mirror_y = false,
        },
        .flags = {
            .buff_dma = true,
            .swap_bytes = true,
        },
    };
    lv_display_t *display = lvgl_port_add_disp(&disp_cfg);
    if (display == NULL) {
        ESP_LOGE(TAG, "Failed to add LVGL display");
        return;
    }

    ESP_LOGI(TAG, "Start circular spectrum");
    lvgl_port_lock(0);
    ui_anim_start(display);
    lvgl_port_unlock();

    ESP_LOGI(TAG, "Display ready");
}
