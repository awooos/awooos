#include "text.h"
#include "basic_display.h"
#include "basic_uart.h"

void hal_print_callback(void *_string)
{
    char *string = (char*)_string;

    hal_basic_display_print(string);
    hal_basic_uart_print(string);
}
