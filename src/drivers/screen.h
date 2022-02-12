#ifndef DRIVER_SCREEN
#define DRIVER_SCREEN

#include "stddef.h"
#include "stdint.h"

typedef struct
{
    size_t hoz_res;
    size_t ver_res;
    size_t pixels_per_scanline;
} VideoMode;

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a; // Reserved, unused
} pixel_t;

#ifdef __cplusplus
extern "C" {
#endif

int screen_init();
VideoMode screen_get_mode();
void screen_get_modes(VideoMode** modes, size_t* count);
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
