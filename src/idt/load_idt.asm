global load_idt
load_idt:
  mov rdx, [rsp+8] ; pointer to IDTR struct
  lidt [rdx]
  ret