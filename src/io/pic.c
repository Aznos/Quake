#include "pic.h"

void pic_configure(uint8_t offsetPic1, uint8_t offsetPic2)
{
  // ICW1
  outb(PIC1_COMMAND_PORT, PIC_ICW1_ICW4 | PIC_ICW1_INITIALIZE);
  io_wait();
  outb(PIC2_COMMAND_PORT, PIC_ICW1_ICW4 | PIC_ICW1_INITIALIZE);
  io_wait();

  // ICW2
  outb(PIC1_DATA_PORT, offsetPic1);
  io_wait();
  outb(PIC2_DATA_PORT, offsetPic2);
  io_wait();

  // ICW3
  outb(PIC1_DATA_PORT, 0x4); // Tell PIC1 it has a slave at IRQ 2
  io_wait();
  outb(PIC2_DATA_PORT, 0x2); // Tell PIC2 its a cascade
  io_wait();

  // ICW4
  outb(PIC1_DATA_PORT, PIC_ICW4_8086);
  io_wait();
  outb(PIC2_DATA_PORT, PIC_ICW4_8086);
  io_wait();

  // Clear registers
  outb(PIC1_DATA_PORT, 0);
  io_wait();
  outb(PIC2_DATA_PORT, 0);
  io_wait();
}

void pic_mask(int irq)
{
  uint8_t port;

  if (irq < 8)
  {
    port = PIC1_DATA_PORT;
  }
  else
  {
    irq -= 8;
    port = PIC2_DATA_PORT;
  }

  uint8_t mask = inb(PIC1_DATA_PORT);
  outb(PIC1_DATA_PORT, mask | (1 << irq));
}

void pic_unmask(int irq)
{
  uint8_t port;

  if (irq < 8)
  {
    port = PIC1_DATA_PORT;
  }
  else
  {
    irq -= 8;
    port = PIC2_DATA_PORT;
  }

  uint8_t mask = inb(PIC1_DATA_PORT);
  outb(PIC1_DATA_PORT, mask & ~(1 << irq));
}

void pic_disable()
{
  outb(PIC1_DATA_PORT, 0xFF);
  io_wait();
  outb(PIC2_DATA_PORT, 0xFF);
  io_wait();
}

void pic_send_eoi(int irq)
{
  if (irq >= 8)
  {
    outb(PIC2_COMMAND_PORT, PIC_CMD_EOI);
  }

  outb(PIC1_COMMAND_PORT, PIC_CMD_EOI);
}

uint16_t pic_read_irq_request_register()
{
  outb(PIC1_COMMAND_PORT, PIC_CMD_READ_IRR);
  outb(PIC2_COMMAND_PORT, PIC_CMD_READ_IRR);
  return inb(PIC2_COMMAND_PORT) | (inb(PIC2_COMMAND_PORT) << 8);
}

uint16_t pic_read_in_service_register()
{
  outb(PIC1_COMMAND_PORT, PIC_CMD_READ_ISR);
  outb(PIC2_COMMAND_PORT, PIC_CMD_READ_ISR);
  return inb(PIC2_COMMAND_PORT) | (inb(PIC2_COMMAND_PORT) << 8);
}