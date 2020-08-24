#ifndef FLAIL_MAIN_H
#define FLAIL_MAIN_H

#include <stddef.h>

// flail_stack_dump() is an assembly stub (in platform-i386/main.asm), which
// call flail_stack_dump_hex() with the argument being the stack pointer (esp).
extern void flail_stack_dump(void);

void flail_wait_forever(void);

void _flail_print_panic(const char *message, const char *function,
        const char *filename, size_t line);

void flail_stack_dump_hex(size_t *_stack);

#endif
