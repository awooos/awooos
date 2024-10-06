#ifndef FLAIL_INTERNAL
#define FLAIL_INTERNAL

#include <stddef.h>

void _flail_print_panic(const char *message, const char *function,
        const char *filename, size_t line);

void flail_print(const char *string);

#endif
