#ifndef HAL_MM_FRAMES_H
#define HAL_MM_FRAMES_H

#include <stddef.h>
#include "placement_allocator.h"
#include "paging.h"

void dmm_set_frame(size_t addr);
void dmm_clear_frame(size_t addr);
size_t dmm_test_frame(size_t addr);
size_t dmm_first_frame();
int dmm_alloc_frame(PageTableEntry *page, int is_kernel, int is_writable);
void dmm_free_frame(PageTableEntry *page);
void dmm_frames_init();

#endif /* HAL_MM_FRAMES_H */
