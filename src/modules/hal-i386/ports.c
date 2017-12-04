#include "ports.h"
#include <stdint.h>

void hal_outb(uint16_t port, uint8_t value)
{
    __asm__ __volatile__ ("outb %0, %1" : : "a" (value), "dN" (port));
}

uint8_t hal_inb(uint16_t port)
{
    uint8_t value;

    __asm__ volatile ("inb %1, %0" : "=a" (value) : "dN" (port));

    return value;
}

uint16_t hal_inw(uint16_t port)
{
    uint16_t value;

    __asm__ volatile ("inw %1, %0" : "=a" (value) : "dN" (port));

    return value;

}

