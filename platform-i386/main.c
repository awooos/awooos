#include <flail.h>
#include <flail/internal.h>
#include <flail/platform.h>
#include <stddef.h>
#include "../src/uint_to_str.h"


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


void flail_stack_dump_with_stack(size_t *stack_start, size_t *_stack_end)
{
    char buffer[UINT64_BUFSIZE];

    int max_frames = 20; // maximum number of frames to print.
    size_t frame;     // pointer to the current frame in the stack.
    size_t ip;        // current instruction pointer.
    size_t stack_end; // point where we should stop.

    if (stack_start == (size_t*)0) {
        FLAIL_GET_STACK_START(frame);
        FLAIL_GET_STACK_END(stack_end);
    } else {
        frame = (size_t)stack_start;
        stack_end = (size_t)_stack_end;
    }
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

#ifndef FLAIL_DONT_DEFINE_STACK_DUMP
void flail_stack_dump()
{
    flail_stack_dump_with_stack(0, 0);
}
#endif


void flail_wait_forever()
{
    while(1) {
        __asm__("cli\nhlt");
    }
}
