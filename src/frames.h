#ifndef HAL_MM_FRAMES_H
#define HAL_MM_FRAMES_H

#include <kernel/hal/mm/placement_allocator.h>
#include <kernel/hal/mm/paging.h>

void set_frame(unsigned int addr);
void clear_frame(unsigned int addr);
unsigned int test_frame(unsigned int addr);
unsigned int first_frame();
int alloc_frame(PageTableEntry *page, int is_kernel, int is_writable);
void free_frame(PageTableEntry *page);
void InitMMFrames();

#endif /* HAL_MM_FRAMES_H */
