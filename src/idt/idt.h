#ifndef IDT_H
#define IDT_H

#include <stdint.h>

typedef struct
{
  uint16_t offset_low;  // bits 0-15 of handler addr
  uint16_t selector;    // code seg selector
  uint8_t ist;          // bits 0-2 = IST#, bits 3-7 = 0
  uint8_t type_attr;    // type | DPL | P
  uint16_t offset_mid;  // bits 16-31 of handler addr
  uint32_t offset_high; // bits 32-63 of handler addr
  uint32_t zero;
} __attribute__((packed)) idt_entry;

typedef struct
{
  uint16_t limit;
  uint64_t base;
} __attribute__((packed)) idt_descriptor;

#define IDT_TYPE_INTERRUPT 0xE // 0x8E for ring-0 interrupt gate
#define IDT_TYPE_TRAP 0xF

#define IDT_FLAG_PRESENT 0x80
#define IDT_DPL_RING0 0x00
#define IDT_DPL_RING3 0x60

#define IDT_TYPE_ATTR(type, dpl) (IDT_FLAG_PRESENT | ((dpl) << 5) | (type))
#define FLAG_SET(x, flag) x |= (flag)
#define FLAG_UNSET(x, flag) x &= ~(flag)

void idt_set_gate(int vec, void (*handler)(void), uint8_t ist, uint8_t type_attr);
void idt_enable_gate(int interrupt);
void idt_disable_gate(int interrupt);
void idt_init(void);
void idt_load(idt_descriptor *idt_desc);

#endif