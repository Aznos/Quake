#include "idt.h"
#include "gdt/gdt.h"

static idt_entry g_idt[256];
static idt_descriptor g_idt_desc = {
    .limit = sizeof(g_idt) - 1,
    .base = (uint64_t)g_idt,
};

/* idt.c */
void idt_set_gate(int vec, void (*handler)(void), uint8_t ist, uint8_t type_attr)
{
  uint64_t addr = (uint64_t)handler;

  g_idt[vec].offset_low = addr & 0xFFFF;
  g_idt[vec].selector = GDT_CODE_SEGMENT;
  g_idt[vec].ist = ist & 0x7;
  g_idt[vec].type_attr = type_attr;
  g_idt[vec].offset_mid = (addr >> 16) & 0xFFFF;
  g_idt[vec].offset_high = (addr >> 32);
  g_idt[vec].zero = 0;
}

__attribute__((interrupt)) static void default_isr(void *frame)
{
  (void)frame;
  for (;;)
    __asm__ volatile("hlt");
}

void idt_init(void)
{
  for (int v = 0; v < 256; ++v)
    idt_set_gate(v, (void (*)(void))default_isr, 0,
                 IDT_TYPE_ATTR(IDT_TYPE_INTERRUPT, 0));

  idt_load(&g_idt_desc);
}

void idt_enable_gate(int interrupt)
{
  FLAG_SET(g_idt[interrupt].type_attr, IDT_FLAG_PRESENT);
}

void idt_disable_gate(int interrupt)
{
  FLAG_UNSET(g_idt[interrupt].type_attr, IDT_FLAG_PRESENT);
}