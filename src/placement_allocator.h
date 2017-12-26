#ifndef HAL_MM_PLACEMENT_ALLOCATOR
#define HAL_MM_PLACEMENT_ALLOCATOR

#define MALLOC_ALIGN 1

void dmm_placement_allocator_init(unsigned int kernel_end);
void *kmalloc_int(unsigned int size, unsigned int flags);

#endif /* HAL_MM_PLACEMENT_ALLOCATOR */
