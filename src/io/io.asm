bits 64
default rel
section .text

global outb
outb:
  mov dx, di
  mov al, sil
  out dx, al
  ret

global inb
inb:
  mov dx, di
  in al, dx
  movzx eax, al
  ret

global enable_interrupts
enable_interrupts:
  sti
  ret

global disable_interrupts
disable_interrupts:
  cli
  ret