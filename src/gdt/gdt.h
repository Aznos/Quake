#ifndef GDT_H
#define GDT_H

#include <stdint.h>

#define i686_GDT_CODE_SEGMENT 0x08
#define i686_GDT_DATA_SEGMENT 0x10

typedef struct
{
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_middle;
  uint8_t access;
  uint8_t flags_limit_hi;
  uint8_t base_high;
} __attribute__((packed)) GDTEntry;

typedef struct {
  uint16_t limit;
  GDTEntry* ptr;
} __attribute__((packed)) GDTDescriptor;

typedef enum {
  GDT_ACCESS_CODE_READABLE = 0x02,
  GDT_ACCESS_DATA_WRITABLE = 0x02,

  GDT_ACCESS_CODE_CONFORMING = 0x04,
  GDT_ACCESS_DATA_DIRECTION_NORMAL = 0x00,
  GDT_ACCESS_DATA_DIRECTION_DOWN = 0x04,

  GDT_ACCESS_DATA_SEGMENT = 0x10,
  GDT_ACCESS_CODE_SEGMENT = 0x18,

  GDT_ACCESS_DESCRIPTOR_TSS = 0x00,

  GDT_ACCESS_RING0 = 0x00,
  GDT_ACCESS_RING1 = 0x20,
  GDT_ACCESS_RING2 = 0x40,
  GDT_ACCESS_RING3 = 0x60,

  GDT_ACCESS_PRESENT = 0x80,
} GDT_ACCESS;

typedef enum {
  GDT_FLAG_64BIT = 0x20,
  GDT_FLAG_32BIT = 0x40,
  GDT_FLAG_16BIT = 0x00,

  GDT_FLAG_GRANULARITY_1B = 0x00,
  GDT_FLAG_GRANULARITY_4K = 0x80,
} GDT_FLAGS;

#define GDT_LIMIT_LOW(limit) ((limit) & 0xFFFF)
#define GDT_BASE_LOW(base) ((base) & 0xFFFF)
#define GDT_BASE_MIDDLE(base) (((base) >> 16) & 0xFF)
#define GDT_FLAGS_LIMIT_HI(limit, flags) ((((limit) >> 16) & 0xF) | ((flags) & 0xF0))
#define GDT_BASE_HIGH(base) (((base) >> 24) & 0xFF)

#define GDT_ENTRY(base, limit, access, flags) { \
  GDT_LIMIT_LOW(limit), \
  GDT_BASE_LOW(base), \
  GDT_BASE_MIDDLE(base), \
  access, \
  GDT_FLAGS_LIMIT_HI(limit, flags), \
  GDT_BASE_HIGH(base) \
}

extern GDTEntry g_GDT[];
extern GDTDescriptor g_GDTDescriptor;

void __attribute__((cdecl)) i686_GDT_Load(GDTDescriptor* descriptor, uint16_t codeSegment, uint16_t dataSegment);
void i686_GDT_init();

#endif