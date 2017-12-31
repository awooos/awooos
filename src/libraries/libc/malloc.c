#include <stddef.h>
#include <string.h>
#include "malloc.h"

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
