#include "bump.h"

static uint64_t phys_cursor = 0;

static inline void *phys_to_virt(uint64_t p)
{
  return (void *)(p + hhdm_req.response->offset);
}

void bump_init(void)
{
  extern uint8_t __kernel_end[];
  phys_cursor = (uint64_t)__kernel_end - 0xffffffff80000000;
  phys_cursor = (phys_cursor + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1); // align to page

  dbg_printf(INFO, "Bump allocator initialized at %p", (void *)phys_cursor);
}

void *early_alloc(size_t bytes, size_t align)
{
  if (align)
    phys_cursor = (phys_cursor + align - 1) & ~(align - 1);
  uint64_t p = phys_cursor;
  phys_cursor += (bytes + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1); // bump whole pages
  return phys_to_virt(p);
}