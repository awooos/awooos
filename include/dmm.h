#ifndef DMM__DMM_H
#define DMM__DMM_H

#include <stddef.h>

typedef void (DMM_PanicFn)(const char *message, const char *function,
        const char *filename, size_t line);

extern DMM_PanicFn *_dmm_panic;
#define dmm_panic(message) _dmm_panic(message, __FUNCTION__, __FILE__, __LINE__)

void dmm_init(DMM_PanicFn *panic_fn);

void dmm_add_memory_region(void *start, size_t length);
void *dmm_malloc(size_t size);
void dmm_free(void *ptr);
void *dmm_realloc(void *ptr, size_t size);

// Tests
void add_dmm_tests();

#endif
