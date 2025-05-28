#ifndef IO_H
#define IO_H

#define UNUSED_PORT 0x80

#include <stdint.h>

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);

void enable_interrupts(void);
void disable_interrupts(void);

static inline void io_wait(void) {
  outb(0x80, 0);
}

#endif