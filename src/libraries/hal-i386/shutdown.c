#include "ports.h"
#include <stdbool.h>
#include <awoo/hal.h>
#include <awoo/modifiers.h>
#include <kernel.h>

void hal_shutdown()
{
    kprint("\r\n");
    kprint("TODO: Implement an ACPI-based hal_shutdown().");
}

// Hard shutdown: Disable interrupts then do a keyboard RESET, instead of using
// ACPI.
void hal_shutdown_hard(UNUSED const char *name, UNUSED void *data,
        UNUSED size_t length)
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

void hal_shutdown_test_fail(UNUSED const char *name, UNUSED void *data,
        UNUSED size_t length)
{
    // If a test failed, try qemu-specific shutdown that returns a nonzero
    // exit code, then fall back to an ormal hard shutdown.
    hal_outb(0xf4, 0x00);
    hal_shutdown_hard(name, data, length);
}
