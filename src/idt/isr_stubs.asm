;===============================================================================
; src/idt/isr_stubs.asm
;
; For exception vectors 0–31 we generate a stub that:
;   - cli               ; disable further interrupts
;   - mov rdi, vector   ; pass the exception number in RDI
;   - call isr_handler  ; C routine that will print & hlt forever
;   - (no iretq! instead a hlt/jmp loop)
;===============================================================================

BITS 64
DEFAULT REL

    extern isr_handler      ; the C handler in which you do your hlt‐loop

%macro ISR_NOERR 1
global isr%1
isr%1:
    cli
    mov   rdi, %1           ; exception number
    call  isr_handler
halt_loop_%1:
    hlt
    jmp   halt_loop_%1
%endmacro

;--- build stubs for vectors 0..31 ---------------------------------------------
ISR_NOERR 0
ISR_NOERR 1
ISR_NOERR 2
ISR_NOERR 3
ISR_NOERR 4
ISR_NOERR 5
ISR_NOERR 6
ISR_NOERR 7
ISR_NOERR 8
ISR_NOERR 9
ISR_NOERR 10
ISR_NOERR 11
ISR_NOERR 12
ISR_NOERR 13
ISR_NOERR 14
ISR_NOERR 15
ISR_NOERR 16
ISR_NOERR 17
ISR_NOERR 18
ISR_NOERR 19
ISR_NOERR 20
ISR_NOERR 21
ISR_NOERR 22
ISR_NOERR 23
ISR_NOERR 24
ISR_NOERR 25
ISR_NOERR 26
ISR_NOERR 27
ISR_NOERR 28
ISR_NOERR 29
ISR_NOERR 30
ISR_NOERR 31

;--- build the table of entry‐points for the first 32 vectors ------------------
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