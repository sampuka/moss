#include "kernel_main.h"

#include "uefi/uefi_con.h"

#include "drivers/screen.h"

#include "application/graphics_test.hpp"

int kernel_main()
{
    uefi_conout_outputstring(u"Hello from kernel!!\r\n");

    screen_init();
    screen_set_resolution(1280, 720);

    graphics_test();

    return 0;
}
