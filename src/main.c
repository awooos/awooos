#include <dmm.h>
#include "placement_allocator.h"
#include "frames.h"
#include "paging.h"

static unsigned int _dmm_end_memory;

void dmm_init(unsigned int *_end_memory)
{
    _dmm_end_memory = (unsigned int)_end_memory;

    dmm_frames_init();
    dmm_paging_init();
}

unsigned int dmm_end_memory()
{
    return _dmm_end_memory;
}
