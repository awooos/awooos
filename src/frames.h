#ifndef HAL_MM_FRAMES_H
#define HAL_MM_FRAMES_H

#include "placement_allocator.h"
#include "paging.h"

void dmm_set_frame(unsigned int addr);
void dmm_clear_frame(unsigned int addr);
unsigned int dmm_test_frame(unsigned int addr);
unsigned int dmm_first_frame();
int dmm_alloc_frame(PageTableEntry *page, int is_kernel, int is_writable);
void dmm_free_frame(PageTableEntry *page);
void dmm_frames_init();

#endif /* HAL_MM_FRAMES_H */
