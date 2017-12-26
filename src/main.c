#include <dmm.h>
#include "placement_allocator.h"
#include "frames.h"
#include "paging.h"

void dmm_init(unsigned int last_used_address, unsigned int end_memory)
{
    dmm_frames_init(end_memory);
    dmm_paging_init(last_used_address);
}
