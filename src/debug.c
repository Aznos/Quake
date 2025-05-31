#include "include/debug.h"

void dgb_putchar(char c)
{
  outb(0xE9, c);
}

void dgb_putstr(const char *s)
{
  while (*s)
  {
    dgb_putchar(*s);
    s++;
  }
}