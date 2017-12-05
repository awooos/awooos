#include "main.h"
#include <awoo.h>
#include <kernel.h>
#include <string.h>
#include <badmalloc.h>
#include <ktest.h>

extern size_t *kernel_end;

void kernel_main(uint32_t magic, void *arg)
{
    hal_init();
    badmalloc_init(kernel_end);
    kprint(AWOO_INFO "\r\n");

    test_run_all();
    if (strcmp(AWOO_BUILD_TYPE, "TEST") == 0) {
        hal_hard_shutdown();
    }
}
