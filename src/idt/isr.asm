[bits 64]

extern isr_handler

global isr0:
isr0:
  push 0 ;error code
  push 0 ;int number
  jmp isr_common

global isr1:
isr1:
  push 0 ;error code
  push 1 ;int number
  jmp isr_common

global isr8:
isr8:
  push 8
  jmp isr_common

isr_common:
  pusha ; save all gp registers

  xor eax, eax
  mov ax, ds
  push eax

  mov ax, 0x10 ; use kernel data seg
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  push ebp ; pass pointer to stack to c
  call isr_handler
  add esp, 4

  pop eax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  popa ; pop what we pushed before
  add esp, 8 ; remove error code and int number
  iret