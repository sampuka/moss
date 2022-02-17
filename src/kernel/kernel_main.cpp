#include "kernel_main.h"

#include "uefi_con.h"

#include "screen.h"

int kernel_main()
{
    uefi_conout_outputstring(u"Hello from kernel!!\r\n");

    screen_init();
    screen_set_resolution(1280, 720);
    VideoMode video_mode = screen_get_mode();

    //uefi_conout_outputstring(u"Size of pixel_t: ");
    //uefi_conout_outputstring_uint_dec(sizeof(pixel_t));
    //uefi_conout_outputstring(u"\r\n");

    size_t x = 0;
    size_t y = 0;
    int xd = 1;
    int yd = 1;
    while (true)
    {
        screen_clear_frame();
        for (uint16_t i = 0; i < 256; i++)
        {
            for (uint16_t j = 0; j < 256; j++)
            {
                screen_set_pixel(x+i, y+j, {static_cast<uint8_t>(i), static_cast<uint8_t>(j), 0, 0});
                if (i == 0 || i == 255 || j == 0 || j == 255)
                {
                    screen_set_pixel(x+i, y+j, {0, 0, 255, 0});
                }
            }
        }

        screen_render_text(10, 10, "Hello :)");

        screen_draw_frame();

        if (x == 0)
        {
            xd = 1;
        }
        if (x == video_mode.hoz_res-256)
        {
            xd = -1;
        }
        if (y == 0)
        {
            yd = 1;
        }
        if (y == video_mode.ver_res-256)
        {
            yd = -1;
        }

        x += xd;
        y += yd;
    }
    return 0;
}
