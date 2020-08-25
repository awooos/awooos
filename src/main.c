#include <flail.h>
#include <flail/platform.h>
#include <stddef.h>
#include "uint_to_str.h"

static unsigned int in_panic = 0;
static const char *info_str = NULL;
static FlailPutcharFn *flail_putchar = NULL;

// Print a string, using the putchar()-equivalent passed to tinker_run_tests().
/// @private
void flail_print(const char *string)
{
    for (char *s = (char*)string; *s; s++) {
        flail_putchar(*s);
    }
}

void flail_init(const char *info_str_, FlailPutcharFn *flail_putchar_)
{
    info_str = info_str_;
    flail_putchar = flail_putchar_;
}

void _flail_print_panic(const char *message, const char *function,
        const char *filename, size_t line)
{
    char buffer[UINT64_BUFSIZE];

    // Prevent recursive kernel panics.
    if (in_panic == 1) {
        return;
    }

    in_panic = 1;

    flail_print("!!! Kernel panic !!!\r\n\r\n");
    flail_print(info_str);
    flail_print("\r\n\r\n");

    flail_print(message);
    flail_print("\r\n\r\n\r\n");

    flail_print("Stack dump:\r\n\r\n");

    flail_stack_dump();

    flail_print("\r\n\r\n");

    flail_print("Kernel panic: ");
    flail_print(message);
    flail_print("\r\n ");
    flail_print(filename);
    flail_print(":");
    flail_print(flail_uint_to_str(buffer, line, 10));
    flail_print(" (");
    flail_print(function);
    flail_print(")\r\n");
}

void _flail_panic(const char *message, const char *function,
        const char *filename, size_t line)
{
    _flail_print_panic(message, function, filename, line);
    flail_wait_forever();
}
