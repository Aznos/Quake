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
    hcf();
}
