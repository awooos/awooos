#include <dmm.h>
#include <badmalloc.h>
#include "hal.h"

void hal_dmm_init()
{
    size_t last_used = ((size_t)badmalloc(0)) + 1;

    dmm_init(last_used, hal_end_memory());
}
