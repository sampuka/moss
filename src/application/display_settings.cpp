#include "display_settings.hpp"

#include "drivers/screen.h"

#include "stdio.h"

void display_settings()
{
    bool finished = false;

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

            snprintf(text, 50, " %2d: %4dx%-4d", display_index, v.hoz_res, v.ver_res);

            if (display_index == set.active_mode)
            {
                text[0] = '>';
            }

            screen_render_text(10, 30 + 20 * (display_index - low_index), text);
        }

        screen_draw_frame();
    }
}