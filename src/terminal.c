#include "include/terminal.h"

extern struct limine_framebuffer *fb;

static size_t cur_col = 0, cur_row = 0;
static size_t cols = 0, rows = 0;
static uint32_t def_fg = 0xFFFFFFFF;
static uint32_t def_bg = 0xFF000000;

static inline void put_pixel(struct limine_framebuffer *fb, size_t x, size_t y, uint32_t color)
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
  size_t x0 = col * CELL, y0 = row * CELL;
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

void terminal_init(struct limine_framebuffer *fb_)
{
  fb = fb_;
  cols = fb->width / CELL;
  rows = fb->height / CELL;

  for (size_t r = 0; r < rows; r++)
  {
    for (size_t c = 0; c < cols; c++)
    {
      draw_cell(fb, c * CELL, r * CELL, 0xFF101010);
    }
  }

  cur_col = cur_row = 0;
}

static void term_putchar(char ch)
{
  if (ch == '\n')
  {
    cur_col = 0;
    cur_row++;
  }
  else
  {
    put_char(fb, cur_col, cur_row, ch, def_fg, def_bg);
    if (cur_col++ >= cols)
    {
      cur_col = 0;
      cur_row++;
    }
  }

  if (cur_row >= rows)
  {
    cur_row = 0;
  }
}

void term_write(const char *s)
{
  while (*s)
  {
    term_putchar(*s++);
  }
}

void term_set_colors(uint32_t fg, uint32_t bg)
{
  def_fg = fg;
  def_bg = bg;
}

static void print_uint(uint64_t v, unsigned base)
{
  char buf[32];
  utoa64(v, buf, base);
  term_write(buf);
}

void term_printf(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);

  for (; *fmt; fmt++)
  {
    if (*fmt != '%')
    {
      term_putchar(*fmt);
      continue;
    }

    fmt++;
    switch (*fmt)
    {
    case '%':
      term_putchar('%');
      break;
    case 'c':
      term_putchar((char)va_arg(ap, int));
      break;
    case 's':
      term_write(va_arg(ap, char *));
      break;

    case 'd':
    case 'i':
      int n = va_arg(ap, int);
      if (n < 0)
      {
        term_putchar('-');
        n = -n;
      }
      print_uint((unsigned)n, 10);
      break;

    case 'u':
      print_uint(va_arg(ap, unsigned), 10);
      break;
    case 'x':
      print_uint(va_arg(ap, unsigned), 16);
      break;
    case 'p':
      term_write("0x");
      print_uint(va_arg(ap, uintptr_t), 16);
      break;
    default:
      term_putchar('?');
      break;
    }
  }

  va_end(ap);
}