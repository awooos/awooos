#include <kernel.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <awoostr.h>

static bool in_panic = false;

void panic_stack_dump_hex(size_t *stack)
{
    kprint("\r\nStack dump:\r\n");
    for (size_t original_stack = (size_t)stack;
            (size_t)stack < ((original_stack + 0x1000) & (size_t)(~(0x1000 - 1)));
            stack++) {
        kprint("0x");
//        kprint(n_to_str_radix(stack, 16));
        kprint(": 0x");
        kprint(n_to_str_radix(*stack, 16));
        kprint("\n");

        if (*stack == 0x0) {
            break;
        }
    }
}

void panic_simple(const char *message)
{
    hal_init();
    kprint("Kernel panic: ");
    kprint(message);
    kprint("\r\n");
}

#define panic(message) _panic(message, __FUNCTION__, __FILE__, __LINE__)
noreturn _panic(const char *message, const char *function,
                const char* filename, size_t line)
{
    panic_simple(message);

    /*
     * Something is causing a recursive panic,
     * so try the simpler fallback panic_simple() function.
     */
    if (!in_panic) {
        in_panic = true;
    }

    while (true) {
        __asm__ volatile ("cli; hlt");
    }
}
