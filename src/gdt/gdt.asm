[bits 64]

global i686_GDT_Load
i686_GDT_Load:
  lgdt [rdi]

  mov ax, dx
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax

  ret