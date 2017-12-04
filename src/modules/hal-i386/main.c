#include <kernel.h>
#include "basic_display.h"
#include "basic_uart.h"

void hal_init()
{
    hal_basic_display_init();
    hal_basic_uart_init();
}
