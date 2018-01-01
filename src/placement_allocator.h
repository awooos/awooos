#ifndef HAL_MM_PLACEMENT_ALLOCATOR
#define HAL_MM_PLACEMENT_ALLOCATOR

#define MALLOC_ALIGN 1

#include <stddef.h>

void dmm_placement_allocator_init(size_t kernel_end);
void *kmalloc_int(size_t size, size_t flags);

#endif /* HAL_MM_PLACEMENT_ALLOCATOR */
