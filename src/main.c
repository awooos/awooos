#include <dmm.h>
#include <stddef.h>
#include "placement_allocator.h"
#include "frames.h"
#include "paging.h"

void dmm_init(size_t last_used_address, size_t end_memory)
{
    dmm_frames_init(end_memory);
    dmm_paging_init();
    dmm_placement_allocator_init(last_used_address);
}
