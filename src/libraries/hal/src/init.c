#include <awoo.h>
#include <ali.h>
#include <dmm.h>
#include <ali/event.h>
#include <flail.h>
#include <hal.h>
#include "magic.h"
#include "panic.h"
#include <stddef.h>
#include <stdbool.h>
#include "basic_display.h"
#include "basic_uart.h"
#include "ports.h"
#include "exceptions.h"
#include "gdt.h"
#include "idt.h"
#include "multiboot.h"

static bool hal_initialized = false;

extern size_t kernel_start;
extern size_t kernel_end;

static size_t hal_kernel_start = (size_t)&kernel_start;
static size_t hal_kernel_end   = (size_t)(&kernel_end) + 1;

void hal_init()
{
    if (hal_initialized) {
        return;
    }

    hal_basic_display_init();
    hal_basic_uart_init();
    hal_gdt_init();
    hal_idt_init();
    hal_exceptions_init();

    flail_init(AWOO_INFO, &kprint);
    dmm_init(&_flail_panic);
    hal_init_panic(&_flail_panic);

    // Get the Multiboot info struct
    MultibootInfo *multiboot_info = ((MultibootInfo*)hal_get_arg());

    // In the multiboot flags, bit 4 and 5 indicate the format:
    // - bit 4 means a.out
    // - bit 5 means ELF
    //
    // These should never be set at the same time.
    // If both are set, there's likely a bug in the bootloader.
    if (((multiboot_info->flags & (1 << 4)) != 0)
        && ((multiboot_info->flags & (1 << 5)) != 0)) {

        hal_panic("multiboot passed flags with bits 4 and 5 set");
    }

    // We need ELF section header information to parse STAB information.
    if ((multiboot_info->flags & (1 << 5)) == 0) {
        hal_panic("multiboot didn't pass ELF section header info");
    }

    // We need ELF, not a.out.
    if ((multiboot_info->flags & (1 << 4)) != 0) {
        hal_panic("multiboot passed a.out header when we're expecting ELF");
    }

    // We expect a memory map to initialize DMM.
    if ((multiboot_info->flags & (1 << 6)) == 0) {
        hal_panic("multiboot didn't pass a memory map");
    }

    // Initialize DMM with available memory regions (as told by multiboot).
    size_t mmap_addr = multiboot_info->mmap_addr;
    size_t mmap_count = ((size_t)multiboot_info->mmap_length) / sizeof(MultibootMemoryMapEntry);

    for (size_t i = 0; i < mmap_count; i++) {
        MultibootMemoryMapEntry *mmap_entry = ((MultibootMemoryMapEntry*)mmap_addr) + i;

        if (mmap_entry->type == MULTIBOOT_MEMORY_MAP_AVAILABLE) {
            // If we get an entry starting at 0x0, make it instead start at
            // 0x1 and decrease it's length by 1 byte.
            if ((size_t)mmap_entry->addr == 0) {
                mmap_entry->addr += 1;
                mmap_entry->length -= 1;
            }

            // If we get an entry that contains the kernel, just skip
            // it for the sake of simplicity.
            //
            // An alternative approach would be to split it into two
            // entries -- e.g.,
            //     <start of actual entry> through <kernel start -1>
            //     <kernel end + 1> through <end of actual entry>
            if (((size_t)mmap_entry->addr >= hal_kernel_start) &&
                    ((size_t)mmap_entry->addr <= hal_kernel_end)) {
                continue;
            }

            // If we get this far, add the memory region to DMM.
            dmm_add_memory_region((void*)mmap_entry->addr, mmap_entry->length);
        }
    }

    ali_init(&dmm_malloc, &dmm_free, &dmm_realloc);
    event_trigger("HAL interrupts enable", NULL, 0);

    hal_initialized = true;
}
