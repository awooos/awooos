#include "ports.h"
#include <stdbool.h>
#include <awoo/hal.h>
#include <kernel.h>

void hal_shutdown()
{
    kprint("\r\n");
    kprint("TODO: Implement an ACPI-based hal_shutdown().");
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

