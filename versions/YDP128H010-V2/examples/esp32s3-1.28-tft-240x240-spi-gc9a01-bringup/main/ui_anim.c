#include "ui_anim.h"

#include <math.h>

#include "display.h"
#include "esp_log.h"

static const char *TAG = "ui_anim";

#define SPECTRUM_CX           (LCD_H_RES / 2)
#define SPECTRUM_CY           (LCD_V_RES / 2)

#define COLOR_BG              0x000000
#define BAR_COUNT             72
#define INNER_RADIUS          52
#define MIN_BAR_LEN           6
#define MAX_BAR_LEN           58

typedef struct {
    int16_t height;
    int16_t target;
} spectrum_bar_t;

static lv_obj_t *s_screen;
static spectrum_bar_t s_bars[BAR_COUNT];

static void polar_to_xy(float angle_deg, int16_t radius, lv_point_precise_t *point)
{
    const float rad = angle_deg * (float)M_PI / 180.0f;
    point->x = SPECTRUM_CX + (lv_value_precise_t)(radius * cosf(rad));
    point->y = SPECTRUM_CY + (lv_value_precise_t)(radius * sinf(rad));
}

static float bar_angle_deg(int index)
{
    return -90.0f + index * (360.0f / BAR_COUNT);
}

static lv_color_t bar_color(int index)
{
    const uint16_t hue = (uint16_t)((index * 360 / BAR_COUNT + 120) % 360);
    return lv_color_hsv_to_rgb(hue, 92, 100);
}

static int16_t fake_bar_level(int index, uint32_t tick_ms)
{
    const float t = tick_ms * 0.001f;
    const float phase = index * 0.38f;
    const float bass = (sinf(t * 2.6f) + 1.0f) * 0.5f;
    const float mid = (sinf(t * 4.8f + phase) + 1.0f) * 0.5f;
    const float treble = (sinf(t * 7.5f - phase * 0.6f) + 1.0f) * 0.5f;
    const float ripple = (sinf(t * 1.8f + phase * 2.1f) + 1.0f) * 0.5f;
    const float beat = (sinf(t * 5.4f) > 0.78f) ? 1.15f : 0.70f;

    float level = bass * 0.22f + mid * 0.34f + treble * 0.28f + ripple * 0.16f;
    level *= beat;

    if (level < 0.0f) {
        level = 0.0f;
    }
    if (level > 1.0f) {
        level = 1.0f;
    }

    return MIN_BAR_LEN + (int16_t)(level * (MAX_BAR_LEN - MIN_BAR_LEN));
}

static void draw_bar(lv_layer_t *layer, int index, int16_t length)
{
    const float angle = bar_angle_deg(index);
    lv_point_precise_t inner;
    lv_point_precise_t outer;

    polar_to_xy(angle, INNER_RADIUS, &inner);
    polar_to_xy(angle, INNER_RADIUS + length, &outer);

    const lv_color_t color = bar_color(index);

    lv_draw_line_dsc_t glow;
    lv_draw_line_dsc_init(&glow);
    glow.color = color;
    glow.width = 5;
    glow.opa = LV_OPA_30;
    glow.round_start = 1;
    glow.round_end = 1;
    glow.p1 = inner;
    glow.p2 = outer;
    lv_draw_line(layer, &glow);

    lv_draw_line_dsc_t core;
    lv_draw_line_dsc_init(&core);
    core.color = color;
    core.width = 3;
    core.opa = LV_OPA_COVER;
    core.round_start = 1;
    core.round_end = 1;
    core.p1 = inner;
    core.p2 = outer;
    lv_draw_line(layer, &core);
}

static void spectrum_draw_event(lv_event_t *event)
{
    lv_layer_t *layer = lv_event_get_layer(event);

    for (int i = 0; i < BAR_COUNT; i++) {
        draw_bar(layer, i, s_bars[i].height);
    }
}

static void spectrum_timer_cb(lv_timer_t *timer)
{
    LV_UNUSED(timer);

    const uint32_t tick = lv_tick_get();

    for (int i = 0; i < BAR_COUNT; i++) {
        s_bars[i].target = fake_bar_level(i, tick + i * 13);

        const int16_t diff = s_bars[i].target - s_bars[i].height;
        if (diff > 0) {
            s_bars[i].height += (diff + 2) / 3;
        } else {
            s_bars[i].height += (diff - 1) / 2;
        }

        if (s_bars[i].height < MIN_BAR_LEN) {
            s_bars[i].height = MIN_BAR_LEN;
        }
        if (s_bars[i].height > MAX_BAR_LEN) {
            s_bars[i].height = MAX_BAR_LEN;
        }
    }

    lv_obj_invalidate(s_screen);
}

void ui_anim_start(lv_display_t *display)
{
    lv_display_set_default(display);

    s_screen = lv_screen_active();
    lv_obj_set_style_bg_color(s_screen, lv_color_hex(COLOR_BG), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(s_screen, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_remove_flag(s_screen, LV_OBJ_FLAG_SCROLLABLE);

    for (int i = 0; i < BAR_COUNT; i++) {
        s_bars[i].height = MIN_BAR_LEN;
        s_bars[i].target = MIN_BAR_LEN;
    }

    lv_obj_add_event_cb(s_screen, spectrum_draw_event, LV_EVENT_DRAW_MAIN, NULL);
    lv_timer_create(spectrum_timer_cb, 33, NULL);
    lv_obj_invalidate(s_screen);

    ESP_LOGI(TAG, "Circular spectrum visualizer started");
}
