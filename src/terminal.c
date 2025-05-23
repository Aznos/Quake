#include "include/terminal.h"

void terminal_init(struct limine_framebuffer *fb)
{
  size_t width = fb->width;
  size_t height = fb->height;

  size_t cols = width / CELL;
  size_t rows = height / CELL;

  static unsigned char grid[256][256];
  for (size_t r = 0; r < rows; r++)
  {
    for (size_t c = 0; c < cols; c++)
    {
      grid[r][c] = ' ';
    }
  }

  for (size_t r = 0; r < rows; r++)
  {
    for (size_t c = 0; c < cols; c++)
    {
      draw_cell(fb, c * CELL, r * CELL, 0xFFFF0000);
    }
  }
}

inline void put_pixel(struct limine_framebuffer *fb, size_t x, size_t y, uint32_t color)
{
  uint32_t *base = (uint32_t *)fb->address;
  size_t pitch_pixels = fb->pitch / 4;
  base[y * pitch_pixels + x] = color;
}

void draw_cell(struct limine_framebuffer *fb, size_t x0, size_t y0, uint32_t color)
{
  for (size_t dy = 0; dy < CELL; dy++)
  {
    for (size_t dx = 0; dx < CELL; dx++)
    {
      put_pixel(fb, x0 + dx, y0 + dy, color);
    }
  }
}

void put_char(struct limine_framebuffer *fb, size_t col, size_t row, unsigned char c, uint32_t fg, uint32_t bg)
{
  size_t x0 = col * CELL;
  size_t y0 = row * CELL;
  draw_cell(fb, x0, y0, bg);

  for (size_t dy = 0; dy < CELL; dy++)
  {
    unsigned char bits = font[c][dy];
    for (size_t dx = 0; dx < CELL; dx++)
    {
      if (bits & (1 << (7 - dx)))
      {
        put_pixel(fb, x0 + dx, y0 + dy, fg);
      }
    }
  }
}

void put_str(struct limine_framebuffer *fb, size_t start_col, size_t start_row, const char *str, uint32_t fg, uint32_t bg)
{
  size_t col = start_col;
  size_t row = start_row;

  while (*str)
  {
    if (*str == '\n')
    {
      col = start_col;
      row++;
    }
    else
    {
      put_char(fb, col, row, *str, fg, bg);
      col++;
    }
    str++;
  }
}