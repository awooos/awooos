#ifndef FLAIL_H
#define FLAIL_H

#include <stddef.h>

typedef int FlailPutcharFn(int);

void flail_init(const char *info_str_, FlailPutcharFn *flail_putchar_);

void _flail_panic(const char *message, const char *function,
        const char *filename, size_t line);

#define flail_panic(message) _flail_panic(message, __FUNCTION__, __FILE__, __LINE__)

// Tests.
void test_flail_intentional_panic(void);

#endif
