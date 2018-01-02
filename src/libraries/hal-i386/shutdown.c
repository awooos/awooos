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

void hal_shutdown_hard()
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

// Used to shut down after test runs, for tests builds.
void hal_test_shutdown(bool success)
{
    if (!success) {
        // If a test failed, try qemu-specific shutdown that returns a nonzero
        // exit code.
        hal_outb(0xf4, 0x00);
    }

    hal_shutdown_hard();
}

// Callbacks.
void hal_shutdown_hard_callback(UNUSED const char *name, UNUSED void *data,
        UNUSED size_t length)
{
    hal_shutdown_hard();
}
