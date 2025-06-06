#ifndef HAL_H
#define HAL_H

#include "gdt.h"
#include "idt/idt.h"
#include "idt/isr.h"
#include "io/irq.h"
#include "include/debug.h"

void HAL_init();

#endif