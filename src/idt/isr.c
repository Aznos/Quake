#include "isr.h"
#include "idt.h"
#include "gdt/gdt.h"
#include "include/framebuffer.h"
#include "include/terminal.h"
#include "utils/string.h"

static size_t log_row = 10;

void isr_initialize()
{
  isr_initialize_gates();
  for (int i = 0; i < 256; i++)
  {
    idt_enable_gate(i);
  }
}

void isr_handler(registers *r)
{
  char num[20];
  char line[32];

  utoa64(r->vector, num, 10);

  kstrcpy(line, "INT ");
  kstrcpy(line + 4, num);

  put_str(fb, 0, log_row, line, 0xFFFFFFFF, 0xFF000000);

  log_row++;
  size_t max_rows = fb->height / CELL;
  if (log_row >= max_rows)
  {
    log_row = 10;
  }
}