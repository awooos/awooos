#include <awoo.h>
#include <ali.h>
#include <dmm.h>
#include <ali/event.h>
#include <flail.h>
#include <hal.h>
#include "interrupts.h"
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
#include "metadata.h"
#include "multiboot.h"

#define MBOOT_FLAG_A_OUT 4
#define MBOOT_FLAG_ELF   5
#define MBOOT_FLAG_MMAP  6

static bool hal_initialized = false;

extern size_t kernel_start;
extern size_t kernel_end;

static size_t hal_kernel_start = (size_t)&kernel_start;
static size_t hal_kernel_end   = (size_t)(&kernel_end) + 1;

void validate_multiboot_info(MultibootInfo *multiboot_info)
{
#define multiboot_flag_set(bit) ((multiboot_info->flags & (1 << bit)) != 0)

    // Multiboot a.out and ELF flags should never be set simultaneously.
    // These should never be set at the same time.
    if (multiboot_flag_set(MBOOT_FLAG_A_OUT)
            && multiboot_flag_set(MBOOT_FLAG_ELF)) {
        hal_panic("invalid multiboot header: can't have both a.out and ELF.");
    }

    // We need ELF, not a.out.
    if (multiboot_flag_set(MBOOT_FLAG_A_OUT)) {
        hal_panic("invalid multiboot header: expected ELF section, got a.out.");
    }

    // We need ELF section header information to parse STAB information.
    if (!multiboot_flag_set(MBOOT_FLAG_ELF)) {
        hal_panic("invalid multiboot header: no ELF section provided.");
    }

    // We expect a memory map to initialize DMM.
    if (!multiboot_flag_set(MBOOT_FLAG_MMAP)) {
        hal_panic("invalid multiboot header: no memory map provided.");
    }
#undef multiboot_flag_set
}

void hal_add_mmap_entry(MultibootMemoryMapEntry *mmap_entry)
{
    if (mmap_entry->type != MULTIBOOT_MEMORY_MAP_AVAILABLE) {
        return;
    }

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
    //     <start of actual entry> through (hal_kernel_start - 1)
    //     (hal_kernel_end + 1) through <end of actual entry>
    if (((size_t)mmap_entry->addr >= hal_kernel_start) &&
            ((size_t)mmap_entry->addr <= hal_kernel_end)) {
        return;
    }

    // If we get this far, add the memory region to DMM.
    dmm_add_memory_region((void*)mmap_entry->addr, mmap_entry->length);
}

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

    flail_init(AWOO_INFO, &print);
    dmm_init(&_flail_panic);
    hal_init_panic(&_flail_panic);

    // Get the Multiboot info struct.
    MultibootInfo *multiboot_info = ((MultibootInfo*)hal_get_arg());

    validate_multiboot_info(multiboot_info);

    // Initialize DMM with available memory regions (as told by multiboot).
    size_t mmap_addr = multiboot_info->mmap_addr;
    size_t mmap_count = ((size_t)multiboot_info->mmap_length) / sizeof(MultibootMemoryMapEntry);
    MultibootMemoryMapEntry *mmap_entries = (MultibootMemoryMapEntry*)mmap_addr;

    for (size_t i = 0; i < mmap_count; i++) {
        hal_add_mmap_entry(mmap_entries + i);
    }

    ali_init(&_dmm_malloc, &_dmm_free, &_dmm_realloc);

    event_trigger("greeter display", hal_metadata());

    hal_enable_interrupts();

    hal_initialized = true;
}
