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

void *malloc(size_t size)
{
    size_t real_size = size + sizeof(MallocHeader);
    MallocHeader *result = (MallocHeader*)mmfns.malloc(real_size);

    if (first == NULL) {
        first = result;
    }

    if (result == NULL) {
        return NULL;
    }

    memset(result, 0, real_size);

    result->data = ((void*)result) + sizeof(MallocHeader);


    return result->data;
}

void free(void *ptr)
{
    MallocHeader *header = (MallocHeader*)(ptr - sizeof(MallocHeader));

    if (header->prev != NULL && header->next != NULL) {
        header->next->prev = header->prev;
        header->prev->next = header->next;
    } else if (header->prev != NULL && header->next == NULL) {
        header->prev->next = NULL;
    } else if (header->prev == NULL && header->next != NULL) {
        header->next->prev = NULL;
    }

    mmfns.free(header);
}

void *calloc(size_t nmemb, size_t size)
{
    // ASSUMPTION: malloc() zeros allocated memory.
    return malloc(nmemb * size);
}

// TODO: Implement realloc().
void *realloc(void *ptr, size_t size)
{
    MallocHeader *header;
    void *new_ptr;
    size_t min_size;

    if (ptr == NULL) {
        return malloc(size);
    }

    header = (MallocHeader*)(ptr - sizeof(MallocHeader));
    new_ptr = malloc(size);
    min_size = (size < header->size) ? size : header->size;

    if (new_ptr == NULL) {
        return NULL;
    }

    memcpy(new_ptr, ptr, min_size);

    return new_ptr;
}
