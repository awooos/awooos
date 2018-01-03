// REQUIREMENTS: Requires size_t (stddef.h); and memset() and memcpy() (string.h).

#include <dmm.h>
#include <stddef.h>
#include <string.h>
#include "main.h"

DMM_MallocHeader *first;

void dmm_add_memory_region(void *start, size_t length)
{
    // TODO
}

DMM_MallocHeader *_dmm_malloc_header_for(void *ptr)
{
    return ((DMM_MallocHeader*)ptr) - 1;
}

void *dmm_low_level_malloc(size_t real_size)
{
    // TODO.
}

void dmm_low_level_free(void *ptr)
{
    // TODO.
}

void *dmm_malloc(size_t size)
{
    size_t real_size = size + sizeof(DMM_MallocHeader);
    DMM_MallocHeader *result = (DMM_MallocHeader*)dmm_low_level_malloc(real_size);

    if (result == NULL) {
        return NULL;
    }

    // NOTE: dmm_malloc() zeroes memory, which isn't what most allocators do.
    // Not sure if that violates the C standard or not, but *shrug*.
    memset(result, 0, real_size);

    result->size = size;
    result->used = 1;
    result->data = (void*)(result + 1);

    return result->data;
}

void dmm_free(void *ptr)
{
    DMM_MallocHeader *header = (DMM_MallocHeader*)(ptr) - 1;

    header->used = 0;

    dmm_low_level_free(header);
}

void *dmm_calloc(size_t nmemb, size_t size)
{
    // ASSUMPTION: dmm_malloc() zeroes allocated memory.
    return dmm_malloc(nmemb * size);
}

void *dmm_realloc(void *ptr, size_t size)
{
    DMM_MallocHeader *header;
    void *new_ptr;
    size_t min_size;

    if (ptr == NULL) {
        return dmm_malloc(size);
    }

    header = (DMM_MallocHeader*)(ptr) - 1;
    // ASSUMPTION: dmm_malloc() zeroes allocated memory.
    new_ptr = dmm_malloc(size);
    min_size = (size < header->size) ? size : header->size;

    if (new_ptr == NULL) {
        return NULL;
    }

    memcpy(new_ptr, ptr, min_size);

    return new_ptr;
}
