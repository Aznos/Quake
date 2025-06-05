#include "include/terminal.h"
#include "include/framebuffer.h"
#include "include/kernel.h"
#include "include/debug.h"
#include "gdt/hal.h"
#include "io/irq.h"
#include "io/keyboard.h"

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
    // we dont need to do anything yet
}

struct
{
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) gdtr_readback;

void kmain(void)
{
    dbg_printf(INFO, "Kernel starting...");

    if (LIMINE_BASE_REVISION_SUPPORTED == false)
        panic();
    if (fb_req.response == NULL || fb_req.response->framebuffer_count < 1)
        panic();

    dbg_printf(INFO, "Framebuffer found: %dx%d, %dBpp",
               fb_req.response->framebuffers[0]->width,
               fb_req.response->framebuffers[0]->height,
               fb_req.response->framebuffers[0]->bpp);

    fb = fb_req.response->framebuffers[0];
    terminal_init(fb);
    HAL_init();

    irq_register_handler(0, timer);
    irq_register_handler(1, handle_keyboard);

    term_printf("Welcome to QuakeOS!\n\n");
    dbg_printf(INFO, "Boot OK");

    for (;;)
    {
        __asm__ volatile("hlt");
    }
}