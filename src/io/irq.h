#ifndef IRQ_H
#define IRQ_H

#include "idt/isr.h"
#include "pic.h"
#include "io.h"
#include "include/terminal.h"
#include "include/debug.h"
#include <stddef.h>

#define PIC_REMAP_OFFSET 0x20

typedef void (*irq_handler_t)(registers *regs);

void irq_handler(registers *regs);
void irq_initialize();
void irq_register_handler(int irq, irq_handler_t handler);

#endif