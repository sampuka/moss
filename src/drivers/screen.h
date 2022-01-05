#ifndef KERNEL_SCREEN_H
#define KERNEL_SCREEN_H

#include <stdint.h>

#define SCREEN_COLS 80
#define SCREEN_ROWS 25

typedef struct
{
    char c;
    char m;
} schar;

void screen_set_char(uint8_t x, uint8_t y, char c);
void screen_set_mod(uint8_t x, uint8_t y, char m);
void screen_set_schar(uint8_t x, uint8_t y, schar sc);

void screen_clear();
void screen_border();

void screen_print_absolute(uint8_t x, uint8_t y, const char* text);

#endif
