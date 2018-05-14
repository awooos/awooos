#ifndef HAL_BASIC_UART_H
#define HAL_BASIC_UART_H

#include <ali/modifiers.h>

void hal_basic_uart_init(UNUSED void *data);
void hal_basic_uart_print(const char *string);

#endif
