#ifndef ISR_H
#define ISR_H

#include <stdint.h>

typedef struct
{
  uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
  uint64_t rsi, rdi, rbp, rdx, rcx, rbx, rax;

  uint64_t vector;
  uint64_t error_code;

  uint64_t rip, cs, rflags, rsp, ss; // pushed by cpu
} __attribute__((packed)) registers;

void isr_handler(registers *regs);
void isr_initialize_gates(void);
void isr_initialize(void);

#endif