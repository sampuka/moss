#include "screen/screen.h"

void main()
{
    screen_clear();

    screen_print_absolute("Hello moss!", 0, 0);

    char* video_memory = (char*) 0xb8000;

    *video_memory = 'X';
}
