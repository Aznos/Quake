#include "pmm.h"

static uint64_t total_pages;
static uint8_t *bitmap;

uint64_t pmm_total_pages(void)
{
  return total_pages;
}

uint64_t pmm_page_size(void)
{
  return PAGE_SIZE;
}

static uint64_t highest_phys(void)
{
  uint64_t top = 0;
  struct limine_memmap_response *mm = memmap_request.response;

  for (uint64_t i = 0; i < mm->entry_count; i++)
  {
    struct limine_memmap_entry *e = mm->entries[i];
    if (e->base + e->length > top)
    {
      top = e->base + e->length;
    }
  }

  return top;
}

void pmm_init()
{
  uint64_t top = highest_phys();
  total_pages = PFN(top) + 1;
  size_t bitmap_bytes = (total_pages + 7) / 8;                      // round up bits->bytes
  bitmap_bytes = (bitmap_bytes + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1); // page align

  dbg_printf(INFO, "PMM: Total pages: %lu, bitmap size: %lu bytes", total_pages, bitmap_bytes);
}