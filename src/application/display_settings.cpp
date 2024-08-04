#include "display_settings.hpp"

#include "drivers/screen.h"

#include "stdio.h"

extern "C" {
int uefi_conin_readkeystroke(uint16_t* c);
int uefi_conin_reset();
}

void display_settings()
{
    bool finished = false;

    uefi_conin_reset();

    while (!finished)
    {
        screen_clear_frame();

        screen_render_text(10, 10, "Display settings");

        VideoModeSet set = screen_video_modes();

        int low_index = set.active_mode - 2;

        if (low_index < 0)
        {
            low_index = 0;
        }

        int high_index = low_index + 5;

        if (high_index >= set.video_mode_size)
        {
            high_index = set.video_mode_size - 1;
        }

        for (int display_index = low_index; display_index < high_index; display_index++)
        {
            VideoMode v = set.video_modes[display_index];

            char text[50];

            snprintf(text, sizeof text, " %2d: %4dx%-4d", display_index, v.hoz_res, v.ver_res);

            if (display_index == set.active_mode)
            {
                text[0] = '>';
            }

            screen_render_text(10, 30 + 20 * (display_index - low_index), text);
        }

        uint16_t key = 0;
        if (uefi_conin_readkeystroke(&key) == 0)
        {
            uefi_conin_reset();

            int next = set.active_mode;

            if ((key == 97) && (set.active_mode < (set.video_mode_size - 1)))
            {
                next += 1;
            }
            else if ((key == 122) && (set.active_mode > 0))
            {
                next -= 1;
            }

            VideoMode next_mode = set.video_modes[next];

            screen_set_resolution(next_mode.hoz_res, next_mode.ver_res);
        }

        screen_draw_frame();
    }
}
