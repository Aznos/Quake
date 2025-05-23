%macro isr_no_err_stub 1
global isr%1
isr%1:
  cli
  push rbp
  mov rbp, rsp
  push rax
  push rbx
  push rcx

  mov rdi, #1
  call isr_handler

  ; pop the registers
  pop rcx
  pop rbx
  pop rax
  leave
  add rsp, 8
  iretq
%endmacro

%macro isr_err_stub 1
global isr%1
isr%1:
  cli
  push rbp
  mov rbp, rsp
  push rax

  mov rdi, #%1
  mov rsi, [rsp+16]
  call isr_err_handler
  pop rax
  leave
  iretq
%endmacro

; generate 0-31
%rep 32
  %if (__counter__ == 8) || (__counter__ == 10) || (__counter__ == 11) \
      || (__counter__ == 12) || (__counter__ == 13) || (__counter__ == 14) \
      || (__counter__ == 17) || (__counter__ == 30)
        isr_err_stub __counter__
  %else
        isr_no_err_stub __counter__
  %endif
  %assign __counter__ __counter__+1
%endrep

; build stub table of addresses
global isr_stub_table
isr_stub_table:
%assign i 0
%rep 32
  dq isr%i%
  %assign i i+1
%endrep