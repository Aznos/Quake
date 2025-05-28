#ifndef PIC_H
#define PIC_H

#define PIC1_COMMAND_PORT 0x20
#define PIC1_DATA_PORT    0x21
#define PIC2_COMMAND_PORT 0xA0
#define PIC2_DATA_PORT    0xA1

#include <stdint.h>
#include "io.h"

enum {
  PIC_ICW1_ICW4 = 0x1,
  PIC_ICW1_SINGLE = 0x2,
  PIC_ICW1_INTERVAL_4 = 0x4,
  PIC_ICW1_LEVEL = 0x8,
  PIC_ICW1_INITIALIZE = 0x10
};

enum {
  PIC_ICW4_8086 = 0x1,
  PIC_ICW4_AUTO_EOI = 0x2,
  PIC_ICW4_BUFFER_MASTER = 0x4,
  PIC_ICW4_BUFFER_SLAVE = 0x8,
  PIC_ICW4_SFNM = 0x10
};

enum {
  PIC_CMD_EOI = 0x20,
  PIC_CMD_READ_IRR = 0x0A,
  PIC_CMD_READ_ISR = 0x0B
};

void pic_configure(uint8_t offsetPic1, uint8_t offsetPic2);
void pic_mask(int irq);
void pic_unmask(int irq);
void pic_disable();
void pic_send_eoi(int irq);
uint16_t pic_read_irq_request_register();
uint16_t pic_read_in_service_register();

#endif