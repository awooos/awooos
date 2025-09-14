#ifndef FLAIL_H
#define FLAIL_H

#include <stddef.h>

typedef int FlailPutcharFn(int);

void flail_init(const char *info_str_, FlailPutcharFn *flail_putchar_);

void flail_panic_impl(const char *message, const char *function,
        const char *filename, size_t line);

#define flail_panic(message) flail_panic_impl(message, __FUNCTION__, __FILE__, __LINE__)

// Tests.
void test_flail_intentional_panic(void);

#endif
