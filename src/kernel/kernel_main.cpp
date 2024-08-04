#include "kernel_main.h"

#include "drivers/screen.h"

#include "application/graphics_test.hpp"
#include "application/display_settings.hpp"

int kernel_main()
{
    screen_init();
    screen_set_resolution(1280, 720);

    display_settings();

    return 0;
}
