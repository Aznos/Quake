global outb
outb:
  [bits 64]
  mov dx, [esp + 4]
  mov al, [esp + 8]
  out dx, al
  ret

global inb
inb:
  [bits 64]
  mov dx, [esp + 4]
  xor eax, rax
  in al, dx
  ret