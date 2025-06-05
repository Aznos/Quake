#ifndef PMM_H
#define PMM_H

#include "include/limine.h"
#include "include/debug.h"
#include <stdint.h>
#include <stddef.h>

#define PAGE_SIZE 4096ULL
#define PFN(x) ((x) >> 12)

extern volatile struct limine_memmap_request memmap_request;
void pmm_init();

#endif