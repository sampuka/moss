#ifndef DRIVER_SCREEN
#define DRIVER_SCREEN

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"
#include "stdint.h"

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a; // Reserved, unused
} __attribute__((packed)) pixel_t;

typedef struct
{
    int hoz_res;
    int ver_res;
    int pixels_per_scanline;
} VideoMode;

typedef struct
{
    VideoMode* video_modes;
    int video_mode_size;
    int active_mode;
} VideoModeSet;

int screen_init();
VideoMode screen_get_mode();
VideoModeSet screen_video_modes();
int screen_set_resolution(size_t desired_hoz_res, size_t desired_ver_res);

void screen_clear_frame();
void screen_swap_back_frames();
void screen_draw_frame();

void screen_set_pixel(size_t x, size_t y, pixel_t p);

void screen_render_char(size_t x, size_t y, const char ch);
void screen_render_text(size_t x, size_t y, const char* text);

#ifdef __cplusplus
}
#endif

#endif
