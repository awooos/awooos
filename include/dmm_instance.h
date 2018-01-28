#ifndef DMM__DMM_INSTANCE_H
#define DMM__DMM_INSTANCE_H

#include <stddef.h>

void *dmm_instance_add_memory_region(void *instance, void *start, size_t length);
void *dmm_instance_malloc(void *instance, size_t size);
void dmm_instance_free(void *instance, void *ptr);
void *dmm_instance_realloc(void *instance, void *ptr, size_t size);

#endif
