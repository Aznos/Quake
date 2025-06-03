#include "isr.h"

static const char *const g_exceptions[] = {
    "Divide by zero error",
    "Debug",
    "Non-maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "",
    "x87 Floating-Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception ",
    "",
    "",
    "",
    "",
    "",
    "",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    ""};

isr_handler_t g_isr_handlers[256];

void isr_initialize()
{
  isr_initialize_gates();
  for (int i = 0; i < 256; i++)
  {
    idt_enable_gate(i);
  }

  dbg_printf(INFO, "ISR initialized with %d handlers", 256);
}

void isr_handler(registers *regs)
{
  if (g_isr_handlers[regs->vector] != NULL)
  {
    g_isr_handlers[regs->vector](regs);
  }
  else if (regs->vector >= 32)
  {
    term_printf("Unhandled interrupt: %d\n", regs->vector);
  }
  else
  {
    term_printf("Exception: %s (vector %d)\n", g_exceptions[regs->vector], regs->vector);
    term_printf("Error code: %lx\n", regs->error_code);
    term_printf("RIP: %lx, CS: %lx, RFLAGS: %lx, RSP: %lx, SS: %lx\n", regs->rip, regs->cs, regs->rflags, regs->rsp, regs->ss);
    term_printf("RAX: %lx, RBX: %lx, RCX: %lx, RDX: %lx\n", regs->rax, regs->rbx, regs->rcx, regs->rdx);
    term_printf("RDI: %lx, RSI: %lx, RBP: %lx, R8: %lx\n", regs->rdi, regs->rsi, regs->rbp, regs->r8);
    term_printf("R9: %lx, R10: %lx, R11: %lx, R12: %lx\n", regs->r9, regs->r10, regs->r11, regs->r12);
    term_printf("R13: %lx, R14: %lx, R15: %lx\n", regs->r13, regs->r14, regs->r15);
    term_printf("System halted.\n\n");

    panic();
  }
}

void isr_register_handler(int interrupt, isr_handler_t handler)
{
  g_isr_handlers[interrupt] = handler;
  idt_enable_gate(interrupt);
}