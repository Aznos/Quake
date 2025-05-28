[bits 64]
default rel

extern isr_handler

%macro PUSH_REGS 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rdi
    push rsi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
%endmacro

%macro POP_REGS 0
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsi
    pop rdi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
%endmacro

%macro ISR_NOERR 1
global isr%1
isr%1:
  push qword 0
  push qword %1
  jmp isr_common
%endmacro

%macro ISR_ERR 1
global isr%1
isr%1:
  push qword %1
  jmp isr_common
%endmacro

%include "src/idt/isrs_gen.inc"

isr_common:
  cli
  PUSH_REGS

  mov rdi, rsp
  call isr_handler

  POP_REGS
  add rsp, 16
  sti
  iretq