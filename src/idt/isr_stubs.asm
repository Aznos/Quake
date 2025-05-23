;-------------------------------------------------------------------------------
; src/idt/isr_stubs.asm
; For exception vectors 0–31 we generate a stub that:
;   - disables further interrupts (cli)
;   - loops forever doing hlt
;-------------------------------------------------------------------------------

BITS 64
DEFAULT REL

%macro EXC_STUB 1
  global isr%1
isr%1:
  cli
.halt_%1:
  hlt
  jmp .halt_%1
%endmacro

; generate one stub for each exception 0..31
EXC_STUB 0
EXC_STUB 1
EXC_STUB 2
EXC_STUB 3
EXC_STUB 4
EXC_STUB 5
EXC_STUB 6
EXC_STUB 7
EXC_STUB 8
EXC_STUB 9
EXC_STUB 10
EXC_STUB 11
EXC_STUB 12
EXC_STUB 13
EXC_STUB 14
EXC_STUB 15
EXC_STUB 16
EXC_STUB 17
EXC_STUB 18
EXC_STUB 19
EXC_STUB 20
EXC_STUB 21
EXC_STUB 22
EXC_STUB 23
EXC_STUB 24
EXC_STUB 25
EXC_STUB 26
EXC_STUB 27
EXC_STUB 28
EXC_STUB 29
EXC_STUB 30
EXC_STUB 31

; and build the jump‑table
global isr_stub_table
isr_stub_table:
  dq isr0
  dq isr1
  dq isr2
  dq isr3
  dq isr4
  dq isr5
  dq isr6
  dq isr7
  dq isr8
  dq isr9
  dq isr10
  dq isr11
  dq isr12
  dq isr13
  dq isr14
  dq isr15
  dq isr16
  dq isr17
  dq isr18
  dq isr19
  dq isr20
  dq isr21
  dq isr22
  dq isr23
  dq isr24
  dq isr25
  dq isr26
  dq isr27
  dq isr28
  dq isr29
  dq isr30
  dq isr31