#include "isr.h"
#include "include/framebuffer.h"
#include "include/terminal.h"
#include "utils/string.h"

void __attribute__((cdecl)) isr_handler(registers *regs)
{
  put_str(fb, 0, 10, "Received interrupt: " + regs->interrupt, 0xFFFFFFFF, 0xFF000000);
}