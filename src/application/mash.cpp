#include "mash.hpp"

#include "drivers/screen.h"

#define MASH_BUFFER_SIZE 10000
#define MASH_INPUT_BUFFER_SIZE 200

char mash_buffer[MASH_BUFFER_SIZE];
char mash_buffer_it = 0;

char mash_input_buffer[MASH_INPUT_BUFFER_SIZE];
char mash_input_buffer_it = 0;

void mash_print()
{
    screen_clear();

    // From bottom up...

    // Print input

    // Print log

    screen_display();
}

void mash_start(size_t screen_width, size_t screen_height)
{
    while (true)
    {
        // Read keyboard events and update input buffer

        // If [enter], lookup and call command
    }

    return;
}
