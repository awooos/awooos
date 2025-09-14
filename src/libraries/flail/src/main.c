#include <awoo.h>
#include <hal.h>
#include <flail.h>
#include <flail/platform.h>
#include <stddef.h>
#include "uint_to_str.h"

static unsigned int in_panic = 0;

void flail_print_panic(const char *message, const char *function,
        const char *filename, size_t line)
{
    char buffer[UINT64_BUFSIZE];

    // Prevent recursive kernel panics.
    if (in_panic == 1) {
        return;
    }

    in_panic = 1;

    hal_print("!!! Kernel panic !!!\r\n\r\n");
    hal_print(AWOO_INFO);
    hal_print("\r\n\r\n");

    hal_print(message);
    hal_print("\r\n\r\n\r\n");

    hal_print("Stack dump:\r\n\r\n");

    flail_stack_dump();

    hal_print("\r\n\r\n");

    hal_print("Kernel panic: ");
    hal_print(message);
    hal_print("\r\n ");
    hal_print(filename);
    hal_print(":");
    hal_print(flail_uint_to_str(buffer, line, 10));
    hal_print(" (");
    hal_print(function);
    hal_print(")\r\n");
}

void flail_panic_impl(const char *message, const char *function,
        const char *filename, size_t line)
{
    flail_print_panic(message, function, filename, line);
    flail_wait_forever();
}
