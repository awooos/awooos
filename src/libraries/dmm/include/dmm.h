#ifndef DMM__DMM_H
#define DMM__DMM_H

#include <stddef.h>

typedef void (DMM_PanicFn)(const char *message, const char *function,
        const char *filename, size_t line);

extern DMM_PanicFn *dmm_pvt_panic;
#define dmm_panic(message) dmm_pvt_panic(message, __func__, __FILE__, __LINE__)

void dmm_init(DMM_PanicFn *panic_fn);

void dmm_add_memory_region(void *start, size_t length);

void *dmm_malloc_(size_t size, const char function[], const char filename[],
        size_t line);
#define dmm_malloc(size) dmm_malloc_(size, __func__, __FILE__, __LINE__)

void dmm_free_(void *ptr, const char function[], const char filename[],
        size_t line);
#define dmm_free(ptr) dmm_free_(ptr, __func__, __FILE__, __LINE__)

void *dmm_realloc_(void *ptr, size_t size, const char function[],
        const char filename[], size_t line);
#define dmm_realloc(ptr, size) dmm_realloc_(ptr, size, __func__, __FILE__, __LINE__)

// Tests
void add_dmm_tests(void);

#endif
