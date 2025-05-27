#include "isr.h"
#include "idt.h"
#include "gdt/gdt.h"
#include "include/framebuffer.h"
#include "include/terminal.h"
#include "utils/string.h"

void isr_initialize()
{
  isr_initialize_gates();
  for (int i = 0; i < 256; i++)
  {
    idt_enable_gate(i);
  }
}

void isr_handler(registers *r)
{
  term_printf("INT %u\n", (unsigned)r->vector);
}