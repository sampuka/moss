#include "screen.h"

#include "libc/string.h"

typedef struct
{
    char c;
    char m;
} screen_char;

#define SCREEN_ADDRESS (screen_char*) 0xb8000

#define SCREEN_COLS 80
#define SCREEN_ROWS 25

void screen_clear()
{
    screen_char sc;
    sc.c = ' ';
    sc.m = 0x0f;

    for (int i = 0; i < SCREEN_COLS*SCREEN_ROWS; i++)
    {
        *(SCREEN_ADDRESS+i) = sc;
    }
}

void screen_print_absolute(const char* text, int x, int y)
{
    int len = strlen(text);

    screen_char sc;
    sc.m = 0x0f;

    for (int i = 0; i < len; i++)
    {
        sc.c = text[i];
        int dest = i+y*SCREEN_COLS;
        if (dest > SCREEN_COLS*SCREEN_ROWS)
        {
            return;
        }
        *(SCREEN_ADDRESS+dest) = sc;
    }
}
