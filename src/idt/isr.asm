[bits 64]
default rel

extern isr_handler


%macro PUSH_REGS 0
    push r15
    push r14
    push r13
    push r12
    push r11
    push r10
    push r9
    push r8
    push rsi
    push rdi
    push rbp
    push rdx
    push rcx
    push rbx
    push rax
%endmacro

%macro POP_REGS 0
    pop  rax
    pop  rbx
    pop  rcx
    pop  rdx
    pop  rbp
    pop  rdi
    pop  rsi
    pop  r8
    pop  r9
    pop  r10
    pop  r11
    pop  r12
    pop  r13
    pop  r14
    pop  r15
%endmacro

%macro ISR_NOERR 1
global isr%1
isr%1:
  push qword 0 ; dummy err code
  push qword %1 ; interrupt number
  jmp isr_common
%endmacro

%macro ISR_ERR 1
global isr%1
isr%1:
  push qword %1 ; interrupt number
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