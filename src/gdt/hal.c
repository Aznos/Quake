#include "hal.h"

void HAL_init()
{
  dbg_printf(INFO, "Initializing HAL...");

  gdt_init();
  idt_init();
  isr_initialize();
  irq_initialize();
}