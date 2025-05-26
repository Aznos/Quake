[bits 64]
default rel

global gdt_load
gdt_load:
  lgdt [rdi]

  mov ax, dx
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax

  push rsi
  lea rax, [rel reload_cs]
  push rax
  retfq

reload_cs:
  ret