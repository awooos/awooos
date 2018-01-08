#include <awoo.h>
#include <ali.h>
#include <dmm.h>
#include <eventually.h>
#include <flail.h>
#include <kernel.h>
#include <stddef.h>
#include <stdbool.h>
#include "basic_display.h"
#include "basic_uart.h"
#include "ports.h"
#include "exceptions.h"
#include "gdt.h"
#include "idt.h"
#include "multiboot.h"

static uint32_t magic;
static void *arg;

extern size_t kernel_end;

static bool hal_initialized = false;

uint32_t hal_get_magic()
{
    return magic;
}

void hal_store_magic(uint32_t magic_, void *arg_)
{
    magic = magic_;
    arg   = arg_;
}

void hal_init()
{
    hal_basic_display_init();
    hal_basic_uart_init();

    if (!hal_initialized) {
        hal_gdt_init();
        hal_idt_init();

        hal_exceptions_init();

        flail_init(AWOO_INFO, &kprint);

        // Get the Multiboot info struct
        MultibootInfo *multiboot_info = ((MultibootInfo*)arg);

        // If bits 4 and 5 are set, Multiboot did something bad!
        // Bit 4 is set if a.out header is passed, bit 5 is set if ELF header
        // is passed - these should not be able to be set at the same time.
        // If they are, this is usually an indication of an error in the
        // bootloader.
        if (((multiboot_info->flags & (1 << 4)) != 0)
            && ((multiboot_info->flags & (1 << 5)) != 0)) {

            panic("multiboot passed flags with bits 4 and 5 set");
        }

        // We don't want a.out stuff as we're compiled to ELF
        if ((multiboot_info->flags & (1 << 4)) != 0) {
            panic("multiboot passed a.out header when we're expecting ELF");
        }

        // If we don't have ELF section header info, it'll be impossible to do
        // parsing of stabs later on
        if ((multiboot_info->flags & (1 << 5)) == 0) {
            panic("multiboot didn't pass ELF section header info");
        }

        // We expect a memory map to initialize DMM
        if ((multiboot_info->flags & (1 << 6)) == 0) {
            panic("multiboot didn't pass a memory map");
        }

        // Initialize DMM with our available memory regions (as told by multiboot)
        size_t mmap_addr = multiboot_info->mmap_addr;
        while (mmap_addr < (multiboot_info->mmap_addr + multiboot_info->mmap_length)) {
            MultibootMemoryMapEntry *mmap_entry = (MultibootMemoryMapEntry*)mmap_addr;

            if (mmap_entry->type == MULTIBOOT_MEMORY_MAP_AVAILABLE) {
                dmm_add_memory_region(mmap_entry->addr, mmap_entry->length);
            }

            mmap_addr = mmap_addr + mmap_entry->size;
        }

        ali_init(&dmm_malloc, &dmm_free, &dmm_realloc);

        eventually_event_trigger_immediate("HAL interrupts enable", NULL, 0);
    }

    hal_initialized = true;
}

int kprint(const char *string) {
    eventually_event_trigger_immediate("kernel print", (char*)string, 0);

    return 0;
}
