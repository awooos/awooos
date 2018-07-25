#ifndef ALI_H
#define ALI_H

#include <ali/text.h>
#include <stdint.h>
#include <stddef.h>

typedef void *(AliMallocFn)(size_t size, const char function[],
        const char filename[], size_t line);
typedef void (AliFreeFn)(void *ptr, const char function[],
        const char filename[], size_t line);
typedef void *(AliReallocFn)(void *ptr, size_t size, const char function[],
        const char filename[], size_t line);

typedef struct ali_memory_manager_functions_s {
    AliMallocFn *malloc;
    AliFreeFn *free;
    AliReallocFn *realloc;
} AliMemoryManagerFunctions;

void ali_init(AliMallocFn *mallocfn, AliFreeFn *freefn,
        AliReallocFn *reallocfn);

void *ali_malloc(size_t size, const char function[],
        const char filename[], size_t line);

void ali_free(void *ptr, const char function[],
        const char filename[], size_t line);

void *ali_calloc(size_t nmemb, size_t size, const char function[],
        const char filename[], size_t line);

void *ali_realloc(void *ptr, size_t size, const char function[],
        const char filename[], size_t line);

// Tests.
void add_ali_tests(void);

#endif
