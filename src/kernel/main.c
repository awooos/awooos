#include <awoo.h>
#include <kernel.h>
#include <stdint.h>
#include <string.h>
#include <badmalloc.h>
#include <ktest.h>
#include <awoo/tests.h>

extern size_t *kernel_end;

void add_tests()
{
    add_awoostr_tests();
}

void kernel_main(uint32_t magic, void *arg)
{
    hal_init();
    badmalloc_init(kernel_end);
    kprint(AWOO_INFO "\r\n");

    add_tests();

    bool continue_booting = test_run_all();

    if (!continue_booting) {
        hal_test_fail_shutdown();
    } else if (strcmp(AWOO_BUILD_TYPE, "TEST") == 0) {
        hal_hard_shutdown();
    }

    // Hooray, tests passed! Now to actually do something.
}
