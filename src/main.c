#include <flail.h>
#include <stddef.h>
#include <ali/str.h>

// stack_dump() is an assembly stub (in libpanic-i386/main.asm), which calls
// panic_stack_dump_hex() with the argument being the stack pointer (esp).
extern void stack_dump();

static unsigned int in_panic = 0;

char *info_str = NULL;

void flail_init(char *info_str_)
{
    info_str = info_str_;
}

void flail_stack_dump_hex(size_t *_stack)
{
    size_t *stack = _stack;

    for (size_t original_stack = (size_t)stack;
            (size_t)stack < ((original_stack + 0x1000) & (size_t)(~(0x1000 - 1)));
            stack++) {
        kprint("0x");
        kprint(n_to_str_radix((size_t)stack, 16));
        kprint(": 0x");
        kprint(n_to_str_radix(*stack, 16));
        kprint("\n");

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

        kprint("!!! Kernel panic !!!\r\n\r\n");
        kprint(info_str);
        kprint("\r\n\r\n");

        kprint(message);
        kprint("\r\n\r\n");

        kprint("Stack dump:\r\n\r\n");

        flail_stack_dump();

        kprint("\r\n\r\n");

        kprint("Kernel panic: ");
        kprint(message);
        kprint("\r\n ");
        kprint(filename);
        kprint(":");
        kprint(str(line));
        kprint(" (");
        kprint(function);
        kprint(")\r\n");
    }

    if (automated == 0) {
        flail_wait_forever();
    }
}
