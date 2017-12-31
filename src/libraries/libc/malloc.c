#include <stddef.h>
#include <string.h>
#include "malloc.h"

// NOTE: malloc() and friends are nonstandard due to zeroing out memory.

MemoryManagerFunctions mmfns;

void memory_manager_init(MallocFn *mallocfn, FreeFn *freefn)
{
    mmfns.malloc = mallocfn;
    mmfns.free = freefn;
}

void *malloc(size_t size)
{
    void *result = mmfns.malloc(size);

    if (result != NULL) {
        memset(result, 0, size);
    }

    return result;
}

void free(void *ptr)
{
    mmfns.free(ptr);
}

void *calloc(size_t nmemb, size_t size)
{
    // ASSUMPTION: malloc() zeros allocated memory.
    return malloc(nmemb * size);
}

// TODO: Implement realloc().
void *realloc(void *ptr, size_t size)
{
    return NULL;
}
