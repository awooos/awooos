#include <kernel.h>
#include "basic_display.h"
#include "basic_uart.h"
#include "ports.h"
#include "events.h"
#include "exceptions.h"
#include "gdt.h"
#include "idt.h"
#include "tiny_multiboot.h"
#include "dmm.h"
#include "../libc/malloc.h"
#include <stddef.h>
#include <stdbool.h>
#include <eventually.h>

static uint32_t magic;
static void *arg;

extern char kernel_comment_start;
extern size_t kernel_end;

static bool hal_initialized = false;

size_t hal_dmm_start_address()
{
    return kernel_end + 1;
}

size_t hal_end_memory()
{
    return ((MultibootInfo*)arg)->mem_upper * 1024;
}

char *hal_compiler_information()
{
    return &kernel_comment_start;
}

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
        hal_events_init();

        hal_gdt_init();
        hal_idt_init();

        hal_exceptions_init();
        dmm_init(hal_dmm_start_address(), hal_end_memory());
        memory_manager_init(&kmalloc, &kfree);

        eventually_event_trigger("HAL interrupts enable", NULL, 0);
    }

    hal_initialized = true;
}

void kprint(const char *string)
{
    hal_basic_display_print(string);
    hal_basic_uart_print(string);
}
