#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define IDT_ENTRIES 256

// Single 64-bit IDT entry
typedef struct
{
  uint16_t isr_low;   // Low 16 bits of ISR address
  uint16_t kernel_cs; // Kernel code segment selector
  uint8_t ist;        // IST index
  uint8_t attributes; // Type and flags (0x8E = present, DPL=0, interrupt gate)
  uint16_t isr_mid;   // Middle 16 bits of ISR address
  uint32_t isr_high;  // High 32 bits of ISR address
  uint32_t reserved;  // Reserved bits set to 0
} __attribute__((packed)) idt_entry_t;

// IDTR structure
typedef struct
{
  uint16_t limit;
  uint64_t base;
} __attribute__((packed)) idtr_t;

extern idt_entry_t idt[IDT_ENTRIES];
extern idtr_t idtr;
extern uint64_t isr_stub_table[];

void idt_set_gate(uint8_t vector, void (*isr)(), uint8_t flags);
void idt_init(void);

#endif