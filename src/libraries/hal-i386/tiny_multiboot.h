#ifndef TINY_MULTIBOOT_H
#define TINY_MULTIBOOT_H

// The bare minimum required to get access to mem_upper.

typedef struct multiboot_info_s
{
    unsigned long flags;
    unsigned long mem_lower;
    unsigned long mem_upper;
    unsigned long boot_device;
    unsigned long cmdline;
    unsigned long mods_count;
    unsigned long mods_addr;
    unsigned long symbol_table[4];
    unsigned long mmap_length;
    unsigned long mmap_addr;
} MultibootInfo;

#endif
