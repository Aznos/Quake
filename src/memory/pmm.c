#include "include/limine.h"
#include "pmm.h"
#include "bump.h"

#define BITMAP_TEST(i) (bitmap[(i) >> 3] & (1u << ((i) & 7)))
#define BITMAP_SET(i) (bitmap[(i) >> 3] |= (1u << ((i) & 7)))
#define BITMAP_CLR(i) (bitmap[(i) >> 3] &= ~(1u << ((i) & 7)))

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

static void mark_range(uint64_t base, uint64_t len, bool used)
{
  // Mark memory ranges to not be used/overwritten
  uint64_t first = PFN(base);
  uint64_t last = PFN(base + len - 1);
  for (uint64_t p = first; p <= last; p++)
  {
    used ? BITMAP_SET(p) : BITMAP_CLR(p);
  }
}

void pmm_init()
{
  uint64_t top = highest_phys();
  total_pages = PFN(top) + 1;
  size_t bitmap_bytes = (total_pages + 7) / 8;                      // round up bits->bytes
  bitmap_bytes = (bitmap_bytes + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1); // page align

  bitmap = early_alloc(bitmap_bytes, PAGE_SIZE);
  kmemset(bitmap, 0xFF, bitmap_bytes);

  struct limine_memmap_response *mm = memmap_request.response;
  for (uint64_t i = 0; i < mm->entry_count; i++)
  {
    struct limine_memmap_entry *e = mm->entries[i];
    if (e->type == LIMINE_MEMMAP_USABLE)
    {
      mark_range(e->base, e->length, false);
    }
  }

  mark_range((uint64_t)__kernel_start, (uint64_t)__kernel_end - (uint64_t)__kernel_start, true);
  mark_range((uint64_t)bitmap, bitmap_bytes, true); // mark bitmap as used

  struct limine_framebuffer_response *fbresp = fb_req.response;
  for (uint64_t i = 0; i < fbresp->framebuffer_count; i++)
  {
    struct limine_framebuffer *fb = fbresp->framebuffers[i];
    uint64_t len = fb->pitch * fb->height;
    mark_range((uint64_t)fb->address, len, true); // mark framebuffer as used
  }

  dbg_printf(INFO, "PMM: Total pages: %lu, bitmap size: %lu bytes", total_pages, bitmap_bytes);
}