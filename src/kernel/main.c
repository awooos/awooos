#include "main.h"
#include <awoo.h>
#include <kernel.h>
#include <string.h>
#include <ktest.h>

void kernel_main(uint32_t magic, void *arg)
{
    hal_init();
    kprint(AWOO_INFO "\r\n");

    test_run_all();
    if (strcmp(AWOO_BUILD_TYPE, "TEST") == 0) {
        hal_hard_shutdown();
    }
}
