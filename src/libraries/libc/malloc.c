#include <stddef.h>
#include "malloc.h"

MemoryManagerFunctions mmfns;

void memory_manager_init(MallocFn *mallocfn, FreeFn *freefn)
{
    mmfns.malloc = mallocfn;
    mmfns.free = freefn;
}

void *malloc(size_t size)
{
    return mmfns.malloc(size);
}

void free(void *ptr)
{
    mmfns.free(ptr);
}
