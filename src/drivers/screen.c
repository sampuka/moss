#include "screen.h"

#include "uefi_gop.h"
#include "bitmap_font.h"

#define BACK_FRAME_HOZ 1920
#define BACK_FRAME_VER 1080
#define BACK_FRAME_SIZE BACK_FRAME_HOZ*BACK_FRAME_VER

VideoMode video_modes[GOP_MAX_MODES_SUPPORTED] = {{0, 0, 0}};
VideoMode active_mode = {0, 0, 0};

uint32_t* front_frame_base = NULL;
size_t frame_size = 0;

pixel_t back_frame1_base[BACK_FRAME_SIZE];
pixel_t back_frame2_base[BACK_FRAME_SIZE];
pixel_t* draw_back_frame = &back_frame1_base[0];
pixel_t* idle_back_frame = &back_frame2_base[0];

pixel_t fground_color;
pixel_t bground_color;

int screen_init()
{
    pixel_t z = {0,0,0,0};
    for (size_t i = 0; i < BACK_FRAME_SIZE; i++)
    {
        back_frame1_base[i] = z;
        back_frame2_base[i] = z;
    }

    for (size_t i = 0; i < GOP_mode_count; i++)
    {
        video_modes[i].hoz_res = GOP_modes[i].info->HorizontalResolution;
        video_modes[i].ver_res = GOP_modes[i].info->VerticalResolution;
        video_modes[i].pixels_per_scanline = GOP_modes[i].info->PixelsPerScanLine;
    }

    active_mode = video_modes[GOP_active_mode];
    front_frame_base = (uint32_t*) gop->Mode->FrameBufferBase;
    frame_size = gop->Mode->FrameBufferSize;

    fground_color = (pixel_t){255, 255, 255, 0};
    bground_color = (pixel_t){  0,   0,   0, 0};

    return 0;
}

VideoMode screen_get_mode()
{
    return active_mode;
}

void screen_video_modes(VideoMode** modes, size_t* count)
{
    *modes = video_modes;
    *count = GOP_mode_count;
}

int screen_set_resolution(size_t desired_hoz_res, size_t desired_ver_res)
{
    for (size_t i = 0; i < GOP_mode_count; i++)
    {
        if (video_modes[i].hoz_res == desired_hoz_res &&
            video_modes[i].ver_res == desired_ver_res)
        {
            int status = uefi_gop_setmode(i);

            if (status == 0)
            {
                active_mode = video_modes[GOP_active_mode];
                front_frame_base = (uint32_t*) gop->Mode->FrameBufferBase;
                frame_size = gop->Mode->FrameBufferSize;
            }

            return status;
        }
    }

    return 1;
}

void screen_clear_frame()
{
    pixel_t z = {0,0,0,0};
    for (size_t i = 0; i < BACK_FRAME_SIZE; i++)
    {
        draw_back_frame[i] = z;
    }
}

void screen_swap_back_frames()
{
    pixel_t* temp = draw_back_frame;
    draw_back_frame = idle_back_frame;
    idle_back_frame = temp;
}

void screen_draw_frame()
{
    uint32_t m = 0;
    pixel_t p = {0,0,0,0};
    for (size_t y = 0; y < active_mode.ver_res; y++)
    {
        for (size_t x = 0; x < active_mode.hoz_res; x++)
        {
            p = draw_back_frame[y*BACK_FRAME_HOZ + x];
            m = (p.r << 16) +
                (p.g <<  8) +
                (p.b <<  0);
            front_frame_base[active_mode.pixels_per_scanline * y + x] = m;
        }
    }

    screen_swap_back_frames();
}

void screen_set_pixel(size_t x, size_t y, pixel_t p)
{
    if (x >= BACK_FRAME_HOZ || y >= BACK_FRAME_VER)
    {
        return;
    }

    draw_back_frame[y * BACK_FRAME_HOZ + x] = p;
}

void screen_render_char(size_t x, size_t y, const char ch)
{
    if (ch < 0 || ch > bitmap_table_size)
    {
        return;
    }

    const unsigned char* bm_ch = bitmap_font[(unsigned char)ch - bitmap_ascii_offset];

    for (size_t i = 0; i < 13; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if (bm_ch[12-i] & (1<<(7-j)))
            {
                screen_set_pixel(x+j, y+i, fground_color);
            }
            else
            {
                screen_set_pixel(x+j, y+i, bground_color);
            }
        }
    }
}

void screen_render_text(size_t x, size_t y, const char* text)
{
    for (size_t i = 0; text[i] != '\0'; i++)
    {
        screen_render_char(x+i*9, y, text[i]);
    }
}
