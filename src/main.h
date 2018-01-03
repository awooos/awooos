#ifndef DMM_MAIN_H
#define DMM_MAIN_H

// ASSUMPTIONS: Requires stdint.h with uint8_t and stddef.h with size_t.

#include <stdint.h>
#include <stddef.h>


typedef void *(DMM_MallocFn)(size_t size);
typedef void (DMM_FreeFn)(void *ptr);

typedef struct dmm_malloc_header_s {
    size_t size;
    uint8_t used;
    void *data;
} DMM_MallocHeader;

typedef struct dmm_memory_manager_functions_s {
    DMM_MallocFn *malloc;
    DMM_FreeFn *free;
} DMM_MemoryManagerFunctions;

DMM_MallocHeader *_dmm_malloc_header_for(void *ptr);

#endif
