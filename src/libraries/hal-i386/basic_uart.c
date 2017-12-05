/* NOTE: THIS UART IMPLEMENTATION IS WRITE-ONLY, TO PRINT DEBUG INFORMATION. */

#include "basic_uart.h"
#include "ports.h"
#include <stdint.h>

// http://wiki.osdev.org/Serial_ports
static uint16_t PORT = 0x3F8;
static uint16_t LINE_CONTROL_REGISTER;

/*
 * UART initialization.
 */
void hal_basic_uart_init()
{
    LINE_CONTROL_REGISTER = PORT + 5;

    hal_outb(PORT + 1, 0x00);    // Disable all interrupts
    hal_outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    hal_outb(PORT + 0, 0x03);    // Set divisor to 3 (low  byte) 38400 baud
    hal_outb(PORT + 1, 0x00);    //                  (high byte)
    hal_outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
    hal_outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    hal_outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

uint8_t hal_basic_uart_transmit_empty()
{
    return hal_inb(LINE_CONTROL_REGISTER) & 0x20; // TODO: Document magic number.
}

void hal_basic_uart_print_character(uint8_t c)
{
    while(hal_basic_uart_transmit_empty() == 0) {
        // FIXME: Unbounded busy loops are very bad!
    }

    hal_outb(PORT, c);
}

/*
 * Very basic function for printing text.
 */
void hal_basic_uart_print(const char *string)
{
    for (; 0 != *string; string++)
    {
        hal_basic_uart_print_character((unsigned char)*string);
    }
}
