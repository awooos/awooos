#ifndef HAL_PORTS_H
#define HAL_PORTS_H

#include <stdint.h>

void hal_outb(uint16_t port, uint8_t value);
uint8_t hal_inb(uint16_t port);
uint16_t hal_inw(uint16_t port);

#endif
