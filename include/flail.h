#ifndef FLAIL_H
#define FLAIL_H

#include <stddef.h>

typedef int FlailPrintFn(const char*);

void flail_init(const char *info_str_, FlailPrintFn *flail_print_);

void _flail_panic(const char *message, const char *function,
        const char *filename, size_t line);

void _flail_print_panic(const char *message, const char *function,
        const char *filename, size_t line);

#define flail_panic(message) _flail_panic(message, __FUNCTION__, __FILE__, __LINE__)

#endif
