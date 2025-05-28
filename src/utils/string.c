#include "string.h"

static const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";

void reverse(char str[], int length)
{
  int start = 0;
  int end = length - 1;

  while (start < end)
  {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }
}

char *utoa64(uint64_t v, char *buf, int base)
{
  if (base < 2 || base > 36)
  {
    buf[0] = '\0';
    return buf;
  }

  char *p = buf;
  if (v == 0)
  {
    *p++ = '0';
    *p = '\0';
    return buf;
  }

  while (v)
  {
    *p++ = digits[v % base];
    v /= base;
  }

  *p = '\0';
  reverse(buf, p - buf);
  return buf;
}

char *itoa64(int64_t v, char *buf, int base)
{
  if (base < 2 || base > 36)
  {
    buf[0] = '\0';
    return buf;
  }

  if (v < 0)
  {
    *buf++ = '-';
    utoa64((uint64_t)(-v), buf, base);
    return buf - 1;
  }

  return utoa64((uint64_t)v, buf, base);
}

size_t kstrlen(const char *s)
{
  const char *p = s;
  while (*p)
    p++;
  return (size_t)(p - s);
}

size_t kstrcpy(char *dst, const char *src)
{
  while ((*dst++ = *src++))
    ;
}