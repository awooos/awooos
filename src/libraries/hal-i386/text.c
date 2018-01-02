#include <awoo/modifiers.h>
#include <stddef.h>
#include "text.h"
#include "basic_display.h"
#include "basic_uart.h"

void hal_print(const char *string)
{
    hal_basic_display_print(string);
    hal_basic_uart_print(string);
}

void hal_print_callback(UNUSED const char *name, void *string,
        UNUSED size_t length)
{
    hal_print((char*)string);
}
