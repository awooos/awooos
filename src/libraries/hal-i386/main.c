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
#include "tiny_multiboot.h"

static uint32_t magic;
static void *arg;

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


uint32_t hal_get_magic()
{
    return magic;
}

void hal_store_magic(uint32_t magic_, void *arg_)
{
    magic = magic_;
    arg   = arg_;
}

// FIXME: Remove this once dmm includes calloc() and realloc().
void *fake_realloc(void *ptr, size_t size)
{
    panic("realloc() isn't implemented!");
    return NULL;
}


void hal_init()
{
    hal_basic_display_init();
    hal_basic_uart_init();

    if (!hal_initialized) {
        hal_gdt_init();
        hal_idt_init();

        hal_exceptions_init();

        // FIXME: Update the following two calls when dmm rewrite is finished.
        dmm_init(hal_dmm_start_address(), hal_end_memory());
        ali_init(&kmalloc, &kfree, &fake_realloc);

        flail_init(AWOO_INFO, &kprint);

        eventually_event_trigger_immediate("HAL interrupts enable", NULL, 0);
    }

    hal_initialized = true;
}

int kprint(const char *string) {
    eventually_event_trigger_immediate("kernel print", (char*)string, 0);

    return 0;
}

