#include "main.h"
#include "badmalloc.h"
#include <awoo.h>
#include <kernel.h>

void kernel_main(uint32_t magic, void *arg)
{
    hal_init();
    kprint(AWOO_INFO);
}
