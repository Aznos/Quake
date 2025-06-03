#ifndef DEBUG_H
#define DEBUG_H

#include "io/io.h"
#include "utils/string.h"
#include <stdarg.h>

void dbg_putchar(char c);
void dbg_putstring(const char *s);
void dbg_printf(const char *fmt, ...);

#endif