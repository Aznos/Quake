#ifndef PMM_H
#define PMM_H

#include "include/debug.h"
#include "include/framebuffer.h"
#include "include/limine_requests.h"

#define PFN(x) ((x) >> 12)

void pmm_init();

#endif