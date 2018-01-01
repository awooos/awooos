#include <stddef.h>
#include <string.h>
#include "malloc.h"

// NOTE: malloc() and friends are nonstandard due to zeroing out memory.

MemoryManagerFunctions mmfns;

MallocHeader *first;

void memory_manager_init(MallocFn *mallocfn, FreeFn *freefn)
{
    mmfns.malloc = mallocfn;
    mmfns.free = freefn;
}

size_t _mm_allocation_size(void *ptr)
{
    MallocHeader *header = ((MallocHeader*)ptr) - 1;

    return header->size;
}

void *malloc(size_t size)
{
    size_t real_size = size + sizeof(MallocHeader);
    MallocHeader *result = (MallocHeader*)mmfns.malloc(real_size);

    if (result == NULL) {
        return NULL;
    }

    // Zeroing allocated memory makes this malloc() implementation nonstandard.
    memset(result, 0, real_size);

    result->size = size;
    result->used = true;
    result->data = (void*)(result + 1);

    return result->data;
}

void free(void *ptr)
{
    MallocHeader *header = (MallocHeader*)(ptr) - 1;

    header->used = false;

    mmfns.free(header);
}

void *calloc(size_t nmemb, size_t size)
{
    // ASSUMPTION: malloc() zeros allocated memory.
    return malloc(nmemb * size);
}

void *realloc(void *ptr, size_t size)
{
    MallocHeader *header;
    void *new_ptr;
    size_t min_size;

    if (ptr == NULL) {
        return malloc(size);
    }

    header = (MallocHeader*)(ptr) - 1;
    // ASSUMPTION: malloc() zeroes allocated memory.
    new_ptr = malloc(size);
    min_size = (size < header->size) ? size : header->size;

    if (new_ptr == NULL) {
        return NULL;
    }

    memcpy(new_ptr, ptr, min_size);

    return new_ptr;
}
