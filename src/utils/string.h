#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

void reverse(char str[], int length);
char *itoa(int value, char *str, int base);
size_t kstrlen(const char *s);
size_t kstrcpy(char *dst, const char *src);

static inline char *utoa64(uint64_t v, char *buf, int base)
{
  return itoa((int)v, buf, base);
}

#endif