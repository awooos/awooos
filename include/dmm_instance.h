#ifndef DMM__DMM_INSTANCE_H
#define DMM__DMM_INSTANCE_H

#include <stddef.h>

void *dmm_instance_add_memory_region(void *instance, void *start, size_t length);

void *_dmm_instance_malloc(void *instance, size_t size, const char function[],
        const char filename[], size_t line);
#define dmm_instance_malloc(instance, size) _dmm_instance_malloc(instance, size, __func__, __FILE__, __LINE__)

void _dmm_instance_free(void *instance, void *ptr, const char function[],
        const char filename[], size_t line);
#define dmm_instance_free(instance, ptr) _dmm_instance_free(instance, ptr, __func__, __FILE__, __LINE__)

void *_dmm_instance_realloc(void *instance, void *ptr, size_t size,
        const char function[], const char filename[], size_t line);
#define dmm_instance_realloc(instance, ptr, size) _dmm_instance_realloc(instance, ptr, size, __func__, __FILE__, __LINE__)


#endif
