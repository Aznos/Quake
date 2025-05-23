#include "include/terminal.h"
#include "include/framebuffer.h"
#include "gdt/hal.h"

__attribute__((used, section(".limine_requests"))) static volatile LIMINE_BASE_REVISION(3);
__attribute__((used, section(".limine_requests"))) static volatile struct limine_framebuffer_request fb_req = {
    .id = LIMINE_FRAMEBUFFER_REQUEST, .revision = 0};
__attribute__((used, section(".limine_requests_start"))) static volatile LIMINE_REQUESTS_START_MARKER;
__attribute__((used, section(".limine_requests_end"))) static volatile LIMINE_REQUESTS_END_MARKER;

static void hcf(void)
{
    for (;;)
        asm("hlt");
}

struct
{
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) gdtr_readback;

void kmain(void)
{
    if (LIMINE_BASE_REVISION_SUPPORTED == false)
        hcf();
    if (fb_req.response == NULL || fb_req.response->framebuffer_count < 1)
        hcf();

    fb = fb_req.response->framebuffers[0];
    terminal_init(fb);

    HAL_init();
    put_str(fb, 0, 0, "Hello world!", 0xFFFFFFFF, 0xFF000000);

    asm volatile("sgdt %0" : "=m"(gdtr_readback));

    if (gdtr_readback.limit != g_GDTDescriptor.limit)
        put_str(fb, 0, 2, "GDT limit mismatch!", 0xFFFF0000, 0);
    else if (gdtr_readback.base != (uint64_t)g_GDTDescriptor.ptr)
        put_str(fb, 0, 3, "GDT base mismatch!", 0xFFFF0000, 0);
    else
        put_str(fb, 0, 2, "GDT looks OK", 0xFF00FF00, 0);

    uint16_t ds, ss;
    asm volatile("mov %%ds, %0" : "=r"(ds));
    asm volatile("mov %%ss, %0" : "=r"(ss));

    if (ds == i686_GDT_DATA_SEGMENT && ss == i686_GDT_DATA_SEGMENT)
        put_str(fb, 0, 4, "DS/SS selectors OK", 0xFF00FF00, 0);
    else
        put_str(fb, 0, 4, "Bad DS/SS selectors!", 0xFFFF0000, 0);

    hcf();
}
