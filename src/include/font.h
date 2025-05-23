#ifndef FONT_H
#define FONT_H

#include <stdint.h>

#define FONT_CHAR_COUNT 256
#define FONT_CHAR_HEIGHT 8

extern const uint8_t font[FONT_CHAR_COUNT][FONT_CHAR_HEIGHT];

#endif