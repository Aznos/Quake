#include "include/debug.h"

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

void dbg_printf(const char *fmt, ...)
{
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
}