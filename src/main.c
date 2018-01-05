#include <flail.h>
#include <stddef.h>
#include <ali/str.h>

typedef void FlailPrintFn(const char*);

// flail_stack_dump() is an assembly stub (in platform-i386/main.asm), which
// call flail_stack_dump_hex() with the argument being the stack pointer (esp).
extern void flail_stack_dump();
static unsigned int in_panic = 0;
char *info_str = NULL;
FlailPrintFn *flail_print = NULL;

void flail_init(char *info_str_, FlailPrintFn *flail_print_)
{
    info_str = info_str_;
    flail_print = flail_print_;
}

void flail_stack_dump_hex(size_t *_stack)
{
    size_t *stack = _stack;

    for (size_t original_stack = (size_t)stack;
            (size_t)stack < ((original_stack + 0x1000) & (size_t)(~(0x1000 - 1)));
            stack++) {
        flail_print("0x");
        flail_print(n_to_str_radix((size_t)stack, 16));
        flail_print(": 0x");
        flail_print(n_to_str_radix(*stack, 16));
        flail_print("\n");

        if (*stack == 0x0) {
            break;
        }
    }
}

void _flail_panic(const char *message, const char *function,
                    const char* filename, size_t line, size_t automated)
{
    /*
     * If we're recursively panicking, we don't want to run this block of code,
     * because this is probably what's causing the recursive panic!
     */
    if (in_panic == 0) {
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
        flail_print(str(line));
        flail_print(" (");
        flail_print(function);
        flail_print(")\r\n");
    }

    if (automated == 0) {
        flail_wait_forever();
    }
}
