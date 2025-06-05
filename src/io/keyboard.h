#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "io/irq.h"
#include "io/io.h"
#include "include/terminal.h"
#include <stdbool.h>
#include <stdint.h>

void handle_keyboard(registers *regs);

#endif