#ifndef ALI_H
#define ALI_H

#include <stdint.h>
#include <stddef.h>

typedef void *(AliMallocFn)(size_t size);
typedef void (AliFreeFn)(void *ptr);
typedef void *(AliReallocFn)(void *ptr, size_t size);

typedef struct ali_memory_manager_functions_s {
    AliMallocFn *malloc;
    AliFreeFn *free;
    AliReallocFn *realloc;
} AliMemoryManagerFunctions;

void ali_init(AliMallocFn *mallocfn, AliFreeFn *freefn,
        AliReallocFn *reallocfn);

void *ali_malloc(size_t size);
void ali_free(void *ptr);
void *ali_calloc(size_t nmemb, size_t size);
void *ali_realloc(void *ptr, size_t size);

#endif
