#include "hal.h"

void HAL_init()
{
  gdt_init();
  idt_init();
  isr_initialize();
  irq_initialize();
}