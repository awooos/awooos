#ifndef DMM__DMM_H
#define DMM__DMM_H

#include <stddef.h>

typedef void (DMM_PanicFn)(const char *message, const char *function,
        const char *filename, size_t line);

extern DMM_PanicFn *_dmm_panic;
#define dmm_panic(message) _dmm_panic(message, __FUNCTION__, __FILE__, __LINE__)

void dmm_init(DMM_PanicFn *panic_fn);

void dmm_add_memory_region(void *start, size_t length);

void *_dmm_malloc(size_t size, const char function[], const char filename[],
        size_t line);
#define dmm_malloc(size) _dmm_malloc(size, __FUNCTION__, __FILE__, __LINE__)

void _dmm_free(void *ptr, const char function[], const char filename[],
        size_t line);
#define dmm_free(ptr) _dmm_free(ptr, __FUNCTION__, __FILE__, __LINE__)

void *_dmm_realloc(void *ptr, size_t size, const char function[],
        const char filename[], size_t line);
#define dmm_realloc(ptr, size) _dmm_realloc(ptr, size, __FUNCTION__, __FILE__, __LINE__)

// Tests
void add_dmm_tests(void);

#endif
