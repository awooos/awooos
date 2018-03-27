#include "interrupts.h"
#include "ports.h"
#include <ali/event.h>
#include <ali/modifiers.h>
#include <kernel.h>

// Hard shutdown: Disable interrupts then do a keyboard RESET, instead
// of using ACPI.
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

// Normal shutdown.
// TODO: Implement an ACPI-based hal_shutdown().
void hal_shutdown(UNUSED const char *name, UNUSED void *data,
        UNUSED size_t length)
{
    event_trigger("HAL shutdown hard", NULL, 0);
}

// QEMU-specific shutdown which, if ran in qemu, will return a nonzero
// exit code.
//
// If ran outside of QEMU, it falls back to a hard shutdown.
void hal_shutdown_test_fail(UNUSED const char *name, UNUSED void *data,
        UNUSED size_t length)
{
    hal_outb(0xf4, 0x00);
    hal_shutdown_hard(name, data, length);
}
