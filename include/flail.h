#ifndef KERNEL_H
#define KERNEL_H

#include <stddef.h>
#include <stdbool.h>

noreturn _panic(const char *message, const char *function,
                const char* filename, size_t line, bool automated);

#define panic(message) _panic(message, __FUNCTION__, __FILE__, __LINE__, false)

#endif
