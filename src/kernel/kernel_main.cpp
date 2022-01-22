#include "uefi_con.h"

#include "screen.h"

extern "C" {

int kernel_main()
{
    uefi_conout_outputstring(u"Hello from kernel!!\r\n");

    screen_init();
    screen_set_resolution(1280, 720);

    for (uint8_t i = 0; i < 255; i++)
    {
        for (uint8_t j = 0; j < 255; j++)
        {
            screen_set_pixel(50+i, 50+j, {i, j, i/3+j/3, 0});
        }
    }

    return 0;
}

} // extern "C"
