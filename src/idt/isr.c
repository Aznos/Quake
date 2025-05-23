#include <stdint.h>
#include "io/io.h"
#include "include/limine.h"
#include "include/terminal.h"
#include "include/framebuffer.h"

char *itoa(int value, char *str, int base);

size_t strlen(const char *str)
{
  size_t len = 0;
  while (str[len] != '\0')
    len++;
  return len;
}

__attribute__((noreturn)) void isr_handler(int vector)
{
  char buf[32];
  itoa(vector, buf, 10);
  int len = strlen(buf);
  buf[len++] = '\0';
  put_str(fb, 0, 3, "Exception: ", 0xFFFFFFFF, 0xFF000000);
  put_str(fb, 12, 4, buf, 0xFFFFFFFF, 0xFF000000);

  for (;;)
    asm("hlt");
}

__attribute__((noreturn)) void isr_err_handler(int int_no, uint64_t error_code)
{
  for (;;)
    asm("hlt");
}

void irq_handler(int irq)
{
  if (irq >= 8)
    outb(0xA0, 0x20);
  outb(0x20, 0x20);
}

char *itoa(int value, char *str, int base)
{
  if (base < 2 || base > 36)
  {
    *str = '\0';
    return str;
  }

  char *ptr = str, *ptr1 = str, tmp_char;
  int tmp_value;

  if (value < 0 && base == 10)
  {
    *ptr++ = '-';
    value = -value;
  }

  tmp_value = value;

  do
  {
    int remainder = tmp_value % base;
    *ptr++ = (remainder < 10) ? (remainder + '0') : (remainder - 10 + 'a');
    tmp_value /= base;
  } while (tmp_value);

  *ptr = '\0';

  ptr1 = (*str == '-') ? str + 1 : str;
  ptr--;
  while (ptr1 < ptr)
  {
    tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }

  return str;
}