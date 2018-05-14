#include "text.h"
#include "basic_display.h"
#include "basic_uart.h"

void hal_print(const char *string)
{
    hal_basic_display_print(string);
    hal_basic_uart_print(string);
}

void hal_print_callback(void *string)
{
    hal_print((char*)string);
}
