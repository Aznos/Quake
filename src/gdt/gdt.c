#include "gdt.h"

GDTEntry g_GDT[] = {
    GDT_ENTRY(0, 0, 0, 0), // NULL descriptor

    GDT_ENTRY(
        0,
        0xFFFFF,
        GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 | GDT_ACCESS_CODE_SEGMENT | GDT_ACCESS_CODE_READABLE,
        GDT_FLAG_64BIT | GDT_FLAG_GRANULARITY_4K),

    GDT_ENTRY(
        0,
        0xFFFFF,
        GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 | GDT_ACCESS_DATA_SEGMENT | GDT_ACCESS_DATA_WRITABLE,
        GDT_FLAG_16BIT | GDT_FLAG_GRANULARITY_4K)};

GDTDescriptor g_GDTDescriptor = {
    sizeof(g_GDT) - 1,
    g_GDT};

void i686_GDT_init()
{
    i686_GDT_Load(&g_GDTDescriptor, 0, i686_GDT_DATA_SEGMENT);
}