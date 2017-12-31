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

static uint32_t magic;
static void *arg;

extern char kernel_comment_start;
extern size_t kernel_end;

static bool hal_initialized = false;

size_t *hal_badmalloc_start_address()
{
    return &kernel_end;
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
    if (!hal_initialized) {
        hal_gdt_init();
        hal_idt_init();
    }

    hal_basic_display_init();
    hal_basic_uart_init();

    if (!hal_initialized) {
        hal_exceptions_init();
        dmm_init(kernel_end + 1, hal_end_memory());
        memory_manager_init(&kmalloc, &kfree);
    }

    hal_initialized = true;
}

void hal_shutdown()
{
    kprint("\r\n");
    kprint("TODO: Implement an ACPI-based hal_shutdown().");
}

void hal_enable_interrupts()
{
    __asm__ volatile ("sti");
}

void hal_disable_interrupts()
{
    __asm__ volatile ("cli");
}

void hal_hard_shutdown()
{
    kprint("\r\n");
    kprint("Doing a hard shutdown.\r\n");

    hal_disable_interrupts();

    while ((hal_inb(0x64) & 2) != 0) {
        // Wait until condition is true before continuing.
    }

    hal_outb(0x64, 0xD1);

    while ((hal_inb(0x64) & 2) != 0) {
        // Wait until condition is true before continuing.
    }

    hal_outb(0x60, 0xFE); // Keyboard RESET.
}

// Used to shut down after test failures.
void hal_test_fail_shutdown()
{
    // Try qemu-specific shutdown that returns a nonzero exit code.
    hal_outb(0xf4, 0x00);
    // Then fall through to a typical hard shutdown, if that didn't work.
    hal_hard_shutdown();
}

void hal_test_shutdown(bool success)
{
    if (success) {
        hal_hard_shutdown();
    } else {
        hal_test_fail_shutdown();
    }
}

void kprint(const char *string)
{
    hal_basic_display_print(string);
    hal_basic_uart_print(string);
}
