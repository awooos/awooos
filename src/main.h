#ifndef FLAIL_MAIN_H
#define FLAIL_MAIN_H

// flail_stack_dump() is an assembly stub (in platform-i386/main.asm), which
// call flail_stack_dump_hex() with the argument being the stack pointer (esp).
extern void flail_stack_dump();

void flail_wait_forever();

void _flail_print_panic(const char *message, const char *function,
        const char *filename, size_t line)

#endif
