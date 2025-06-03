#include "gdt.h"

gdt_entry g_GDT[] = {
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

gdt_descriptor g_GDTDescriptor = {
    sizeof(g_GDT) - 1,
    g_GDT};

void gdt_init()
{
    gdt_load(&g_GDTDescriptor, GDT_CODE_SEGMENT, GDT_DATA_SEGMENT);
    dbg_printf(INFO, "GDT initialized with %d entries", sizeof(g_GDT) / sizeof(gdt_entry));
}