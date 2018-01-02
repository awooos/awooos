#include <kernel.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <awoostr.h>
#include <awoo.h>
#include <eventually.h>

// stack_dump() is an assembly stub (in libpanic-i386/main.asm), which calls
// panic_stack_dump_hex() with the argument being the stack pointer (esp).
extern void stack_dump();

static bool in_panic = false;

void panic_stack_dump_hex(size_t *_stack)
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

noreturn _panic(const char *message, const char *function,
                    const char* filename, size_t line, bool automated)
{
    eventually_event_trigger_immediate("HAL interrupts disable", NULL, 0);

    /*
     * If we're recursively panicking, we don't want to run this block of code,
     * because this is probably what's causing the recursive panic!
     */
    if (!in_panic) {
        in_panic = true;

        eventually_event_trigger_immediate("HAL init", NULL, 0);

        kprint("!!! Kernel panic !!!\r\n\r\n");
        kprint(AWOO_INFO);
        kprint("\r\n\r\n");

        kprint(message);
        kprint("\r\n\r\n");

        kprint("Stack dump:\r\n\r\n");

        stack_dump();

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

    if (automated) {
        eventually_event_trigger_immediate("HAL shutdown hard", NULL, 0);
    }


    while (true) {
        __asm__ volatile ("cli\r\nhlt");
    }
}
