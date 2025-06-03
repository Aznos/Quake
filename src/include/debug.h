#ifndef DEBUG_H
#define DEBUG_H

#include "io/io.h"
#include "utils/string.h"
#include <stdarg.h>

enum debug_level
{
  DEBUG = 0,
  INFO = 1,
  WARNING = 2,
  ERROR = 3,
  CRITICAL = 4,
};

void dbg_putchar(char c);
void dbg_putstring(const char *s);
void dbg_printf(enum debug_level level, const char *fmt, ...);

#endif