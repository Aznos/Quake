#include "include/debug.h"

static const char *const color[] = {
    [DEBUG] = "\033[2;37m",
    [INFO] = "\033[37m",
    [WARNING] = "\033[1;33m",
    [ERROR] = "\033[1;31m",
    [CRITICAL] = "\033[1;37;41m",
};

static const char *const tag[] = {
    [DEBUG] = "[DEBUG] ",
    [INFO] = "[INFO] ",
    [WARNING] = "[WARNING] ",
    [ERROR] = "[ERROR] ",
    [CRITICAL] = "[CRITICAL] ",
};

static const char *const color_reset = "\033[0m";

void dbg_putchar(char c)
{
  outb(0xE9, c);
}

void dbg_putstring(const char *s)
{
  while (*s)
  {
    dbg_putchar(*s++);
  }
}

static void print_uint(uint64_t v, unsigned base)
{
  char buf[32];
  utoa64(v, buf, base);
  dbg_putstring(buf);
}

void dbg_printf(enum debug_level level, const char *fmt, ...)
{
  dbg_putstring(color[level]);
  dbg_putstring(tag[level]);
  dbg_putstring(color_reset);

  va_list ap;
  va_start(ap, fmt);

  for (; *fmt; ++fmt)
  {
    if (*fmt != '%')
    {
      dbg_putchar(*fmt);
      continue;
    }

    ++fmt;

    int longness = 0;
    while (*fmt == 'l')
    {
      ++longness;
      ++fmt;
    }

    switch (*fmt)
    {
    case '%':
      dbg_putchar('%');
      break;

    case 'c':
      dbg_putchar((char)va_arg(ap, int));
      break;

    case 's':
      dbg_putstring(va_arg(ap, char *));
      break;

    case 'd':
    case 'i':
    {
      long long v = longness ? va_arg(ap, long long)
                             : va_arg(ap, int);
      if (v < 0)
      {
        dbg_putchar('-');
        v = -v;
      }
      print_uint((uint64_t)v, 10);
      break;
    }

    case 'u':
    {
      uint64_t v = longness ? va_arg(ap, unsigned long long)
                            : va_arg(ap, unsigned);
      print_uint(v, 10);
      break;
    }

    case 'x':
    {
      uint64_t v = longness ? va_arg(ap, unsigned long long)
                            : va_arg(ap, unsigned);
      print_uint(v, 16);
      break;
    }

    case 'p':
      dbg_putstring("0x");
      print_uint((uint64_t)va_arg(ap, void *), 16);
      break;

    default:
      dbg_putchar('?');
      break;
    }
  }

  va_end(ap);
  dbg_putstring("\n");
}