#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

void reverse(char str[], int length);
char *itoa64(int64_t v, char *buf, int base);
char *utoa64(uint64_t v, char *buf, int base);
size_t kstrlen(const char *s);
size_t kstrcpy(char *dst, const char *src);
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

#endif