#ifndef HAL__PANIC_H
#define HAL__PANIC_H

typedef void (Hal_PanicFn)(const char *message, const char *function,
        const char *filename, size_t line);

extern Hal_PanicFn *_hal_panic;
#define hal_panic(message) _hal_panic(message, __FUNCTION__, __FILE__, __LINE__)

#endif
