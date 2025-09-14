#ifndef DMM__DMM_INSTANCE_H
#define DMM__DMM_INSTANCE_H

#include <stddef.h>

void *dmm_instance_add_memory_region(void *instance, void *start, size_t length);

void *dmm_instance_malloc_(void *instance, size_t size, const char function[],
        const char filename[], size_t line);
#define dmm_instance_malloc(instance, size) dmm_instance_malloc_(instance, size, __func__, __FILE__, __LINE__)

void dmm_instance_free_(void *instance, void *ptr, const char function[],
        const char filename[], size_t line);
#define dmm_instance_free(instance, ptr) dmm_instance_free_(instance, ptr, __func__, __FILE__, __LINE__)

void *dmm_instance_realloc_(void *instance, void *ptr, size_t size,
        const char function[], const char filename[], size_t line);
#define dmm_instance_realloc(instance, ptr, size) dmm_instance_realloc_(instance, ptr, size, __func__, __FILE__, __LINE__)


#endif
