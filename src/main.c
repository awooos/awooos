#include <flail.h>
#include <stddef.h>
#include "main.h"
#include "uint_to_str.h"

static unsigned int in_panic = 0;
static const char *info_str = NULL;
FlailPrintFn *flail_print = NULL;


void flail_init(const char *info_str_, FlailPrintFn *flail_print_)
{
    info_str = info_str_;
    flail_print = flail_print_;
}

void flail_stack_dump_hex(size_t *_stack)
{
    size_t *stack = _stack;
    char buffer[UINT64_BUFSIZE];

    for (size_t original_stack = (size_t)stack;
            (size_t)stack < ((original_stack + 0x1000) & (size_t)(~(0x1000 - 1)));
            stack++) {
        flail_print("0x");
        flail_print(flail_uint_to_str(buffer, (size_t)stack, 16));
        flail_print(": 0x");
        flail_print(flail_uint_to_str(buffer, *stack, 16));
        flail_print("\n");

        if (*stack == 0x0) {
            break;
        }
    }
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
    flail_print("\r\n\r\n");

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
