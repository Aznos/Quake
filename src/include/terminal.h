#ifndef TERMINAL_H
#define TERMINAL_H

#define CELL 8

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "include/font.h"
#include "include/limine.h"

void terminal_init(struct limine_framebuffer *fb);
inline void put_pixel(struct limine_framebuffer *fb, size_t x, size_t y, uint32_t color);
void draw_cell(struct limine_framebuffer *fb, size_t x0, size_t y0, uint32_t color);
void put_char(struct limine_framebuffer *fb, size_t col, size_t row, unsigned char c, uint32_t fg, uint32_t bg);
void put_str(struct limine_framebuffer *fb, size_t start_col, size_t start_row, const char *str, uint32_t fg, uint32_t bg);

#endif