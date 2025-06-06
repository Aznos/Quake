#include "irq.h"

irq_handler_t g_irq_handlers[16];

void irq_handler(registers *regs)
{
  int irq = regs->vector - PIC_REMAP_OFFSET;
  if (g_irq_handlers[irq] != NULL)
  {
    g_irq_handlers[irq](regs);
  }
  else
  {
    term_printf("Unhandled IRQ: %d\n", irq);
  }

  pic_send_eoi(irq);
}

void irq_initialize()
{
  pic_configure(PIC_REMAP_OFFSET, PIC_REMAP_OFFSET + 8);
  dbg_printf(INFO, "PIC remapped");

  for (int i = 0; i < 16; i++)
  {
    isr_register_handler(PIC_REMAP_OFFSET + i, irq_handler);
  }

  dbg_printf(INFO, "IRQ initialized with %d handlers", 16);
  enable_interrupts();
  dbg_printf(INFO, "Interrupts enabled");
}

void irq_register_handler(int irq, irq_handler_t handler)
{
  g_irq_handlers[irq] = handler;
}