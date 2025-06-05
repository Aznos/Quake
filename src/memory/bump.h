#ifndef BUMP_H
#define BUMP_H

#include <stdint.h>
#include <stddef.h>
#include "include/limine_requests.h"
#include "include/debug.h"

#define PAGE_SIZE 4096ULL

extern uint8_t __kernel_start[];
extern uint8_t __kernel_end[];

void *early_alloc(size_t bytes, size_t align);
void bump_init(void);

#endif