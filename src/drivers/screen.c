#include "screen.h"

#include "uefi_gop.h"

VideoMode video_modes[GOP_MAX_MODES_SUPPORTED] = {{0, 0, 0}};
VideoMode active_mode = {0, 0, 0};

uint32_t* frame_base = NULL;
size_t frame_size = 0;

int screen_init()
{
    for (size_t i = 0; i < GOP_mode_count; i++)
    {
        video_modes[i].hoz_res = GOP_modes[i].info->HorizontalResolution;
        video_modes[i].ver_res = GOP_modes[i].info->VerticalResolution;
        video_modes[i].pixels_per_scanline = GOP_modes[i].info->PixelsPerScanLine;
    }

    active_mode = video_modes[GOP_active_mode];
    frame_base = (uint32_t*) gop->Mode->FrameBufferBase;
    frame_size = gop->Mode->FrameBufferSize;

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
            }

            return status;
        }
    }

    return 1;
}

void screen_set_pixel(size_t x, size_t y, pixel_t p)
{
    if (x >= active_mode.hoz_res || y >= active_mode.ver_res)
    {
        return;
    }

    uint32_t m = (p.r << 16) +
                 (p.g <<  8) +
                 (p.b <<  0);

    frame_base[active_mode.pixels_per_scanline * y + x] = m;
}
