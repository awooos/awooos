#ifndef FLAIL_H
#define FLAIL_H

#include <stddef.h>

typedef int FlailPrintFn(const char*);

void flail_init(const char *info_str_, FlailPrintFn *flail_print_);

void _flail_panic(const char *message, const char *function,
                const char* filename, const char *line, size_t automated);

#define FLAIL_STR(x) #x

#define flail_panic(message) _flail_panic(message, __FUNCTION__, __FILE__, FLAIL_STR(__LINE__), 0)

#endif
