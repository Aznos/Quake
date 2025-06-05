#pragma once

#include "limine.h"

extern volatile struct limine_memmap_request         memmap_request;
extern volatile struct limine_framebuffer_request    fb_req;

__attribute__((used,section(".limine_requests")))
static volatile struct limine_hhdm_request hhdm_req = {
    .id = LIMINE_HHDM_REQUEST, .revision = 0
};