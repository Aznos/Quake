#include "include/terminal.h"
#include "include/framebuffer.h"
#include "include/kernel.h"
#include "gdt/hal.h"
#include "io/irq.h"

__attribute__((used, section(".limine_requests"))) static volatile LIMINE_BASE_REVISION(3);
__attribute__((used, section(".limine_requests"))) static volatile struct limine_framebuffer_request fb_req = {
    .id = LIMINE_FRAMEBUFFER_REQUEST, .revision = 0};
__attribute__((used, section(".limine_requests_start"))) static volatile LIMINE_REQUESTS_START_MARKER;
__attribute__((used, section(".limine_requests_end"))) static volatile LIMINE_REQUESTS_END_MARKER;

void panic()
{
    for (;;)
    {
        __asm__("cli; hlt");
    }
}

void timer(registers *regs)
{
    term_printf(".");
}

struct
{
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) gdtr_readback;

void kmain(void)
{
    if (LIMINE_BASE_REVISION_SUPPORTED == false)
        panic();
    if (fb_req.response == NULL || fb_req.response->framebuffer_count < 1)
        panic();

    fb = fb_req.response->framebuffers[0];
    terminal_init(fb);
    HAL_init();
    irq_register_handler(0, timer);

    term_printf("Boot OK - framebuffer %ux%u\n\n", fb->width, fb->height);

    for (;;)
    {
        __asm__ volatile("hlt");
    }
}
