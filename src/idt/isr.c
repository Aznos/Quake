#include <stdint.h>

typedef struct
{
  uint64_t rip, cs, rflags, rsp, ss;
} __attribute__((packed)) register_t;

__attribute__((noreturn)) void isr_handler(int int_no)
{
  for (;;)
    asm("hlt");
}

__attribute__((noreturn)) void isr_err_handler(int int_no, uint64_t error_code)
{
  for (;;)
    asm("hlt");
}

void irq_handler(int irq)
{
  if (irq >= 8)
    outb(0xA0, 0x20);
  outb(0x20, 0x20);
}