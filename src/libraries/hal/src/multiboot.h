#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stdint.h>

typedef struct multiboot_info_s
{
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t boot_device;
    uint32_t cmdline;
    uint32_t mods_count;
    uint32_t mods_addr;
    uint32_t symbol_table[4];
    uint32_t mmap_length;
    uint32_t mmap_addr;
} MultibootInfo;

enum multiboot_memory_map_type
{
    MULTIBOOT_MEMORY_MAP_UNKNOWN = 0,
    MULTIBOOT_MEMORY_MAP_AVAILABLE = 1,
    MULTIBOOT_MEMORY_MAP_RESERVED = 2,
    MULTIBOOT_MEMORY_MAP_ACPI_RECLAIMABLE = 3,
    MULTIBOOT_MEMORY_MAP_NVS = 4,
    MULTIBOOT_MEMORY_MAP_BAD_RAM = 5,
};

typedef struct multiboot_memory_map_s
{
    uint32_t size;
    uint64_t addr;
    uint64_t length;
    uint32_t type;
} MultibootMemoryMapEntry;

#endif
