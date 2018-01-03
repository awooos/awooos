#ifndef DMM_H
#define DMM_H

#include <stddef.h>

void dmm_add_memory_region(void *start, size_t length);
void *dmm_malloc(size_t size);
void dmm_free(void *ptr);

// If the DMM_INTRUSIVE macro is defined, alias malloc() and free()
// to the dmm ones.
#ifdef DMM_INTRUSIVE
#define malloc dmm_malloc
#define free dmm_free
#endif

#endif
