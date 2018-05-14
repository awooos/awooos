// REQUIREMENTS: Requires size_t (stddef.h); and memset() and memcpy() (string.h).

#include <dmm.h>
#include <dmm_instance.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "main.h"
#include "header.h"
#include "instance.h"

DMM_MallocHeader *dmm_global_instance = DMM_UNASSIGNED_REGION;

void dmm_add_memory_region(void *start, uint64_t length)
{
    void *result = dmm_instance_add_memory_region(dmm_global_instance, start, length);

    if (dmm_global_instance == DMM_UNASSIGNED_REGION || dmm_global_instance == NULL) {
        if (result != DMM_UNASSIGNED_REGION && result != NULL) {
            dmm_global_instance = result;
        }
    }
}

DMM_MallocHeader *dmm_get_first_free_chunk(size_t size)
{
    return dmm_instance_get_first_free_chunk(dmm_global_instance, size);
}

void *_dmm_malloc(size_t size, const char function[], const char filename[],
        size_t line)
{
    return _dmm_instance_malloc(dmm_global_instance, size, function,
            filename, line);
}

void _dmm_free(void *ptr, const char function[], const char filename[],
        size_t line)
{
    _dmm_instance_free(dmm_global_instance, ptr, function, filename, line);
}

void *_dmm_realloc(void *ptr, size_t size, const char function[],
        const char filename[], size_t line)
{
    return _dmm_instance_realloc(dmm_global_instance, ptr, size, function,
            filename, line);
}
