#ifndef HAL__HAL_H
#define HAL__HAL_H

#include <stddef.h>

typedef void (Hal_PanicFn)(const char *message, const char *function,
        const char *filename, size_t line);

extern Hal_PanicFn *_hal_panic;
#define hal_panic(message) _hal_panic(message, __FUNCTION__, __FILE__, __LINE__)

void hal_init(Hal_PanicFn *panic_fn);
void hal_register_events();

int kprint(const char *string);

// Tests.
void add_hal_tests();

#endif
