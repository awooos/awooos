// REQUIREMENTS: Requires size_t (stddef.h); and memset() and memcpy() (string.h).

#include <dmm.h>
#include <dmm_instance.h>
#include <stddef.h>
#include <string.h>
#include "main.h"
#include "header.h"
#include "instance.h"

void *dmm_instance_add_memory_region(void *instance, void *start, size_t length)
{
    DMM_MallocHeader *header = (DMM_MallocHeader*)start;
    header->magic = DMM_HEADER_MAGIC;
    header->size = length - sizeof(DMM_MallocHeader);
    header->used = 0;
    header->data = (void*)(header + 1);
    header->next = DMM_UNASSIGNED_REGION;

    if (instance != DMM_UNASSIGNED_REGION && instance != NULL) {
        DMM_MallocHeader *last = (DMM_MallocHeader *)instance;

        while (1) {
            if (last->magic != DMM_HEADER_MAGIC) {
                dmm_panic("memory region header had invalid magic");
            }

            if (last->next == DMM_UNASSIGNED_REGION) {
                last->next = header;
                break;
            }

            last = last->next;
        }
    }

    return (void *)header;
}

DMM_MallocHeader *dmm_instance_get_first_free_chunk(void *instance, size_t size)
{
    DMM_MallocHeader *chunk = (DMM_MallocHeader *)instance;
    if (chunk == DMM_UNASSIGNED_REGION || chunk == NULL) {
        return NULL;
    }

    while (1) {
        if (chunk->magic != DMM_HEADER_MAGIC) {
            dmm_panic("memory region header had invalid magic");
        }

        if ((chunk->size >= size) && (chunk->used == 0)) {
            return chunk;
        }

        chunk = chunk->next;
        if (chunk == DMM_UNASSIGNED_REGION) {
            return NULL;
        }
    }

    return NULL;
}

void *dmm_instance_malloc(void *instance, size_t size)
{
    DMM_MallocHeader *result = dmm_instance_get_first_free_chunk(instance, size);
    if (result == NULL) {
        return NULL;
    }

    if (result->magic != DMM_HEADER_MAGIC) {
        dmm_panic("memory region header had invalid magic");
    }

    // Calculate the size of the memory chunk after the allocated region.
    size_t next_size = result->size - (size + sizeof(DMM_MallocHeader));

    // Set the header to contain this region's exact size, and set it as used.
    result->used = 1;
    result->size = size;

    // NOTE: dmm_malloc() zeroes memory, which isn't what most allocators do.
    // Not sure if that violates the C standard or not, but *shrug*.
    memset(result->data, 0, size);

    // Create a new header after the data, if the remaining data size is
    // large enough to fit the header.
    if (next_size > 0) {
        void *next = (void *)((size_t)(result + 1) + size);
        DMM_MallocHeader *next_header = (DMM_MallocHeader*)next;
        memset(next, 0, sizeof(DMM_MallocHeader));

        next_header->magic = DMM_HEADER_MAGIC;
        next_header->size = next_size;
        next_header->used = 0;
        next_header->data = (void*)(next_header + 1);
        next_header->next = result->next;

        // Set the header of this chunk to point to the new header.
        result->next = next_header;
    }

    return result->data;
}

void dmm_instance_free(void *instance, void *ptr)
{
    (void)instance; // TODO: does this require an instance?
    DMM_MallocHeader *header = (DMM_MallocHeader*)(ptr) - 1;
    if (header->magic != DMM_HEADER_MAGIC) {
        dmm_panic("memory region header had invalid magic");
    }

    header->used = 0;

    // TODO: merge this chunk into the previous/next chunks if they are also
    // marked as free.
}

// TODO: dmm_realloc() should attempt to resize existing chunk rather
// than just allocating a new one and memcpy()ing.
void *dmm_instance_realloc(void *instance, void *ptr, size_t size)
{
    DMM_MallocHeader *header;
    void *new_ptr;
    size_t min_size;

    if (ptr == NULL) {
        return dmm_malloc(size);
    }

    header = (DMM_MallocHeader*)(ptr) - 1;
    if (header->magic != DMM_HEADER_MAGIC) {
        dmm_panic("memory region header had invalid magic");
    }

    // ASSUMPTION: dmm_malloc() zeroes allocated memory.
    new_ptr = dmm_malloc(size);
    min_size = (size < header->size) ? size : header->size;

    if (new_ptr == NULL) {
        return NULL;
    }

    memcpy(new_ptr, ptr, min_size);

    return new_ptr;
}
