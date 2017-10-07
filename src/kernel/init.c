#include "init.h"
#include "badmalloc.h"
#include <kernel/hal_basic_display.h>

void kernel_init(uint32_t magic, void *arg)
{
    hal_basic_display_print("Hello, world!\nmeep\r\nmoop\r\n");
}
