#include "include/terminal.h"
#include "include/framebuffer.h"
#include "include/kernel.h"
#include "gdt/hal.h"

__attribute__((used, section(".limine_requests"))) static volatile LIMINE_BASE_REVISION(3);
__attribute__((used, section(".limine_requests"))) static volatile struct limine_framebuffer_request fb_req = {
    .id = LIMINE_FRAMEBUFFER_REQUEST, .revision = 0};
__attribute__((used, section(".limine_requests_start"))) static volatile LIMINE_REQUESTS_START_MARKER;
__attribute__((used, section(".limine_requests_end"))) static volatile LIMINE_REQUESTS_END_MARKER;

static void hcf(void)
{
    for (;;)
    {
        __asm__("cli; hlt");
    }
}

void panic()
{
    hcf();
}

struct
{
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) gdtr_readback;

static inline void force_fault_with_r14(uint64_t val)
{
    __asm__ volatile(
        "mov %0,  %%r14   \n\t"
        "xor %%eax, %%eax \n\t"
        "div %%eax        \n\t"
        :
        : "r"(val)
        : "r14", "rax", "rdx");
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

    term_printf("Boot OK - framebuffer %ux%u\n\n", fb->width, fb->height);

    force_fault_with_r14(9843);

    hcf();
}
