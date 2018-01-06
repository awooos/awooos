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

#endif
