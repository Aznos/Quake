[bits 64]

global i686_GDT_Load
i686_GDT_Load:
  ;save frame
  push rbp
  mov rbp, rsp

  ;load gdt
  mov rax, [rbp + 16]
  lgdt [rax]

  ;reload code segs
  mov ax, [rbp + 24]
  push rax
  lea rax, [rel .reload_cs]
  push rax
  retfq

.reload_cs:
  ;load data segs
  mov ax, [rbp + 32]
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax

  ;restore frame
  mov rsp, rbp
  pop rbp
  ret