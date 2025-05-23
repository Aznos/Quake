BITS 64
DEFAULT REL

global load_idt
load_idt:
  lidt [rdi]
  ret