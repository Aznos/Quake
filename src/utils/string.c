#include "string.h"

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

char *itoa(int value, char *str, int base)
{
  if (base < 2 || base > 36)
  {
    str[0] = '\0'; // Invalid base
    return str;
  }

  bool isNegative = false;
  int i = 0;

  if (value == 0)
  {
    str[i++] = '0';
    str[i] = '\0';
    return str;
  }

  if (value < 0 && base == 10)
  {
    isNegative = true;
    value = -value;
  }

  while (value != 0)
  {
    int remainder = value % base;
    str[i++] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
    value /= base;
  }

  if (isNegative)
  {
    str[i++] = '-';
  }

  str[i] = '\0';
  reverse(str, i);

  return str;
}