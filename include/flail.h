#ifndef KERNEL_H
#define KERNEL_H

#include <stddef.h>

void _flail_panic(const char *message, const char *function,
                const char* filename, size_t line, size_t automated);

#define flail_panic(message) _flail_panic(message, __FUNCTION__, __FILE__, #__LINE__, 0)

#endif
