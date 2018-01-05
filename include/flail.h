#ifndef KERNEL_H
#define KERNEL_H

#include <stddef.h>
#include <stdbool.h>

noreturn _flail_panic(const char *message, const char *function,
                const char* filename, size_t line, bool automated);

#define flail_panic(message) _flail_panic(message, __FUNCTION__, __FILE__, ""__LINE__, false)
#define panic(message) flail_panic(message)

#endif
