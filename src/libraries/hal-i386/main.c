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

        // Initialize DMM with our available memory regions (as told by multiboot)
        MultibootInfo *multiboot_info = ((MultibootInfo*)arg);
        size_t mmap_addr = multiboot_info->mmap_addr;
        while (mmap_addr < (multiboot_info->mmap_addr + multiboot_info->mmap_length)) {
            MultibootMemoryMapEntry *mmap_entry = (MultibootMemoryMapEntry*)mmap_addr;

            if (mmap_entry->type == MULTIBOOT_MEMORY_MAP_AVAILABLE) {
                dmm_add_memory_region(mmap_entry->addr, mmap_entry->length);
            }

            mmap_addr = mmap_addr + mmap_entry->size;
        }

        ali_init(&dmm_malloc, &dmm_free, &dmm_realloc);

        flail_init(AWOO_INFO, &kprint);

        eventually_event_trigger_immediate("HAL interrupts enable", NULL, 0);
    }

    hal_initialized = true;
}

int kprint(const char *string) {
    eventually_event_trigger_immediate("kernel print", (char*)string, 0);

    return 0;
}

