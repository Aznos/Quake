#include <stdint.h>
#define PIC1_CMD 0x20
#define PIC1_DATA 0x21
#define PIC2_CMD 0xA0
#define PIC2_DATA 0xA1

static void io_wait(void)
{
  asm volatile("outb %al, $0x80" : : "a"(0));
}

void pic_remap(int offset1, int offset2)
{
  // start init
  outb(PIC1_CMD, 0x11);
  io_wait();
  outb(PIC2_CMD, 0x11);
  io_wait();

  // set offsets
  outb(PIC1_DATA, offset1);
  io_wait();
  outb(PIC2_DATA, offset2);
  io_wait();

  // cascade
  outb(PIC1_DATA, 0x04);
  io_wait();
  outb(PIC2_DATA, 0x02);
  io_wait();

  // env info
  outb(PIC1_DATA, 0x01);
  io_wait();
  outb(PIC2_DATA, 0x01);
  io_wait();

  // clear masks
  outb(PIC1_DATA, 0x0);
  outb(PIC2_DATA, 0x0);
}