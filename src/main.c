#include <flail.h>
#include <stddef.h>
#include "main.h"
#include "uint_to_str.h"

#if defined(__i386__) && __i386__
#    define FLAIL_GET_STACK_START(r) __asm__("mov %%ebp, %0" : "=r"(r))
#elif defined(__x86_64__) && __x86_64__
#    define FLAIL_GET_STACK_START(r) __asm__("mov %%rbp, %0" : "=r"(r))
#endif

#if defined(__i386__) && __i386__
#    define FLAIL_GET_STACK_END(r) __asm__("mov %%esp, %0" : "=r"(r))
#elif defined(__x86_64__) && __x86_64__
#    define FLAIL_GET_STACK_END(r) __asm__("mov %%rsp, %0" : "=r"(r))
#endif


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

void flail_stack_dump_hex(size_t *stack_start, size_t *_stack_end)
{
    char buffer[UINT64_BUFSIZE];

    int max_frames = 20;
    size_t frame; // stack pointer
    size_t ip;
    size_t stack_end;

    (void)stack_start;
    (void)_stack_end;
    //if (stack_start == (size_t*)0) {
        FLAIL_GET_STACK_START(frame);
        FLAIL_GET_STACK_END(stack_end);
    //} else {
    //    frame = *stack_start;
    //    stack_end = *_stack_end;
    //}
    for (int i = 0; i < max_frames; i++) {
        size_t *frame_ptr = (size_t*)frame;
        frame = frame_ptr[0];
        ip = frame_ptr[1];

        if (frame < stack_end) {
            return;
        }

        flail_print("0x");
        flail_print(flail_uint_to_str(buffer, frame, 16));
        flail_print(": 0x");
        flail_print(flail_uint_to_str(buffer, ip, 16));
        flail_print("\n");
    }
    flail_print("[...]\n");
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
