#include <kernel.h>
#include "basic_display.h"
#include "basic_uart.h"
#include "ports.h"
#include <stddef.h>

void hal_init()
{
    hal_basic_display_init();
    hal_basic_uart_init();
}

void hal_shutdown()
{
    kprint("\r\n");
    kprint("TODO: Implement an ACPI-based hal_shutdown().");
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
