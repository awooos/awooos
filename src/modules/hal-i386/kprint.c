#include <kernel.h>
#include "basic_display.h"
#include "basic_uart.h"

void kprint(const char *string)
{
    hal_basic_display_print(string);
    hal_basic_uart_print(string);
}

