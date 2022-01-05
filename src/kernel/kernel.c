#include "libc/string.h"
#include "drivers/screen.h"

void main()
{
    screen_clear();
    screen_border();

    const char* welcome_message = "Welcome to Moss!";

    screen_print_absolute((SCREEN_COLS-strlen(welcome_message))/2, 5, welcome_message);
}
