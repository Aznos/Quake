#ifndef ISR_H
#define ISR_H

#include <stdint.h>

typedef struct {
  uint32_t ds; // data seg pushed by us
  uint32_t edi, esi, ebp, kern_esp, ebx, edx, ecx, eax; // pusha
  uint32_t interrupt, error;
  uint32_t eip, cs, eflags, esp, ss; // pushed automatically by cpu
} __attribute__((packed)) registers;

void __attribute__((cdecl)) isr_handler(registers* regs);

#endif