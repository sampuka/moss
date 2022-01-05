#include "screen.h"

#include "libc/string.h"

schar* const screen_memory = (schar*)0xb8000;

void screen_set_char(uint8_t x, uint8_t y, char c)
{
    if (x < SCREEN_COLS && y < SCREEN_ROWS)
    {
        screen_memory[y*SCREEN_COLS+x].c = c;
    }
}

void screen_set_mod(uint8_t x, uint8_t y, char m)
{
    if (x < SCREEN_COLS && y < SCREEN_ROWS)
    {
        screen_memory[y*SCREEN_COLS+x].m = m;
    }
}

void screen_set_schar(uint8_t x, uint8_t y, schar sc)
{
    if (x < SCREEN_COLS && y < SCREEN_ROWS)
    {
        screen_memory[y*SCREEN_COLS+x] = sc;
    }
}

void screen_clear()
{
    schar sc;
    sc.c = ' ';
    sc.m = 0x0f;

    for (int i = 0; i < SCREEN_COLS*SCREEN_ROWS; i++)
    {
        screen_memory[i] = sc;
    }
}

void screen_border()
{
    schar sc;
    sc.c = '#';
    sc.m = 0x0f;

    for (int i = 0; i < SCREEN_COLS; i++)
    {
        screen_set_schar(i, 0, sc);
        screen_set_schar(i, SCREEN_ROWS-1, sc);
    }

    for (int i = 0; i < SCREEN_ROWS; i++)
    {
        screen_set_schar(0, i, sc);
        screen_set_schar(SCREEN_COLS-1, i, sc);
    }
}

void screen_print_absolute(uint8_t x, uint8_t y, const char* text)
{
    int len = strlen(text);

    schar sc;
    sc.m = 0x0f;

    for (int i = 0; i < len; i++)
    {
        sc.c = text[i];
        screen_set_schar(x+i, y, sc);
    }
}
