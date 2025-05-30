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

void *memcpy(void *dest, const void *src, size_t n)
{
  uint8_t *pdest = (uint8_t *)dest;
  const uint8_t *psrc = (const uint8_t *)src;

  for (size_t i = 0; i < n; i++)
  {
    pdest[i] = psrc[i];
  }

  return dest;
}

void *memset(void *s, int c, size_t n)
{
  uint8_t *p = (uint8_t *)s;

  for (size_t i = 0; i < n; i++)
  {
    p[i] = (uint8_t)c;
  }

  return s;
}

void *memmove(void *dest, const void *src, size_t n)
{
  uint8_t *pdest = (uint8_t *)dest;
  const uint8_t *psrc = (const uint8_t *)src;

  if (src > dest)
  {
    for (size_t i = 0; i < n; i++)
    {
      pdest[i] = psrc[i];
    }
  }
  else if (src < dest)
  {
    for (size_t i = n; i > 0; i--)
    {
      pdest[i - 1] = psrc[i - 1];
    }
  }

  return dest;
}

int memcmp(const void *s1, const void *s2, size_t n)
{
  const uint8_t *p1 = (const uint8_t *)s1;
  const uint8_t *p2 = (const uint8_t *)s2;

  for (size_t i = 0; i < n; i++)
  {
    if (p1[i] != p2[i])
    {
      return p1[i] < p2[i] ? -1 : 1;
    }
  }

  return 0;
}