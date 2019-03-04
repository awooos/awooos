// REQUIREMENTS:
// - stddef.h: size_t

#include <dmm.h>
#include <dmm_instance.h>
#include <stddef.h>
#include "dmm_string.h"
#include "main.h"
#include "header.h"
#include "instance.h"

void dmm_call_location(DMM_CallLocation *call_location,
        const char function[], const char filename[], size_t line)
{
    _dmm_strncpy_null(call_location->function, function,
            sizeof(call_location->function));
    _dmm_strncpy_null(call_location->filename, filename,
            sizeof(call_location->filename));

    call_location->line = line;
}

void dmm_consolidate(void *instance)
{
    for (DMM_MallocHeader *curr = (DMM_MallocHeader*)instance;
            curr != NULL && curr->next != NULL;
            curr = curr->next) {
        if (!curr->used && !curr->next->used) {
            continue;
        }

        if ((DMM_MallocHeader*)((size_t)curr->data + 1) != curr->next) {
            continue;
        }

        curr->size += curr->next->size + sizeof(curr->next);
        curr->next = curr->next->next;
    }
}

void *dmm_instance_add_memory_region(void *instance, void *start, size_t length)
{
    DMM_MallocHeader *header = (DMM_MallocHeader*)start;

    if (length == 0) {
        dmm_panic("memory region has size of zero");
    }

    if (start == NULL) {
        dmm_panic("cannot add NULL memory region");
    }

    header->magic = DMM_HEADER_MAGIC;
    header->size = length - sizeof(DMM_MallocHeader);
    if (header->size <= 0) {
        dmm_panic("memory region is too small for header");
    }

    header->used = 0;
    header->data = (void*)(header + 1);
    header->next = DMM_UNASSIGNED_REGION;
    if (instance == NULL) {
        header->instance = start;
    } else {
        header->instance = instance;
    }

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

    dmm_consolidate(instance);

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

        if (chunk->instance != instance) {
            dmm_panic("memory region had unexpected instance");
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

void *_dmm_instance_malloc(void *instance, size_t size, const char function[],
        const char filename[], size_t line)
{
    DMM_MallocHeader *result = dmm_instance_get_first_free_chunk(instance, size);
    if (result == NULL) {
        return NULL;
    }

    if (result->magic != DMM_HEADER_MAGIC) {
        _dmm_panic("memory region header had invalid magic (_dmm_instance_malloc)", function, filename, line);
    }

    // Calculate the size of the memory chunk after the allocated region.
    size_t next_size = result->size - (size + sizeof(DMM_MallocHeader));

    // Set the header to contain this region's exact size, and set it as used.
    result->used = 1;
    result->size = size;

    dmm_call_location(&(result->call_location), function, filename, line);

    // NOTE: dmm_malloc() zeroes memory, which isn't what most allocators do.
    // Not sure if that violates the C standard or not, but *shrug*.
    _dmm_memset(result->data, 0, size);

    // Create a new header after the data, if the remaining data size is
    // large enough to fit the header.
    if (next_size > sizeof(DMM_MallocHeader)) {
        void *next = (void *)((size_t)(result + 1) + size);
        DMM_MallocHeader *next_header = (DMM_MallocHeader*)next;
        _dmm_memset(next, 0, sizeof(DMM_MallocHeader));

        next_header->magic = DMM_HEADER_MAGIC;
        next_header->size = next_size;
        next_header->used = 0;
        next_header->data = (void*)(next_header + 1);
        next_header->next = result->next;
        next_header->instance = result->instance;

        // Set the header of this chunk to point to the new header.
        result->next = next_header;
    }

    return result->data;
}

void _dmm_instance_free(void *instance, void *ptr, const char function[],
        const char filename[], size_t line)
{
    DMM_MallocHeader *header = (DMM_MallocHeader*)(ptr) - 1;

    if (ptr == NULL) {
        return;
    }

    if (header->instance != instance) {
        _dmm_panic("memory region has unexpected instance in _dmm_instance_free", function, filename, line);
    }

    if (header->magic != DMM_HEADER_MAGIC) {
        _dmm_panic("memory region header had invalid magic in _dmm_instance_free", function, filename, line);
    }

    header->used = 0;

    dmm_consolidate(instance);
}

// TODO: Have _dmm_instance_realloc() resize a chunk if possible.
void *_dmm_instance_realloc(void *instance, void *ptr, size_t size, const char *function,
        const char *filename, size_t line)
{
    DMM_MallocHeader *header;
    void *new_ptr;
    size_t min_size;

    if (ptr == NULL) {
        return _dmm_instance_malloc(instance, size, function, filename, line);
    }

    // Check for memory clobbering.
    header = (DMM_MallocHeader*)(ptr) - 1;
    if (header->magic != DMM_HEADER_MAGIC) {
        _dmm_panic("memory region header had invalid magic in _dmm_instance_realloc", function, filename, line);
    }

    // Allocate new memory chunk.
    new_ptr = _dmm_instance_malloc(instance, size, function, filename, line);
    if (new_ptr == NULL) {
        return NULL;
    }

    // Zero new memory chunk, to prevent data leakage.
    _dmm_memset(new_ptr, 0, size);

    // Copy data to new memory address.
    min_size = (size < header->size) ? size : header->size;
    _dmm_memcpy(new_ptr, ptr, min_size);

    // Release the original allocation.
    _dmm_instance_free(instance, ptr, function, filename, line);

    return new_ptr;
}
