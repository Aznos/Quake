#include "include/idt.h"

idt_entry_t idt[IDT_ENTRIES] __attribute__((aligned(0x10)));
idtr_t idtr;

void idt_set_gate(uint8_t vector, void (*handler)(), uint8_t flags)
{
  uint64_t addr = (uint64_t)handler;
  idt[vector].isr_low = addr & 0xFFFF;
  idt[vector].kernel_cs = 0x08;
  idt[vector].ist = 0;
  idt[vector].attributes = flags;
  idt[vector].isr_mid = (addr >> 16) & 0xFFFF;
  idt[vector].isr_high = (addr >> 32) & 0xFFFFFFFF;
  idt[vector].reserved = 0;
}

extern void load_idt(idtr_t *idtr_ptr);
extern void isr_stub_table();

void idt_init(void)
{
  idtr.base = (uint64_t)&idt;
  idtr.limit = sizeof(idt_entry_t) * IDT_ENTRIES - 1;

  for (int i = 0; i < IDT_ENTRIES; i++)
  {
    idt_set_gate(i, (void (*)())isr_stub_table, 0);
  }

  for (int vec = 0; vec < 32; vec++)
  {
    idt_set_gate(vec, (void (*)())((uint8_t *)&isr_stub_table + vec * 8), 0x8E);
  }

  // TODO: remap pic

  load_idt(&idtr);
  __asm__ volatile("sti");
}