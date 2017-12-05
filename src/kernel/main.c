#include "main.h"
#include "badmalloc.h"
#include <awoo.h>
#include <kernel.h>

void kernel_main(uint32_t magic, void *arg)
{
    hal_init();
    kprint(AWOO_INFO "\r\n");

    //test_run();
    //if (strcmp(AWOO_BUILD_TYPE, "TEST") == 0) {
        hal_hard_shutdown();
    //}
}
