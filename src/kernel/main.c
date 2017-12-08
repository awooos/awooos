#include <awoo.h>
#include <kernel.h>
#include <stdint.h>
#include <string.h>
#include <badmalloc.h>
#include <ktest.h>
#include <awoo/tests.h>
#include <awoostr.h>

extern size_t *kernel_end;

#define ADD_TESTS(TEST_CATEGORY) { \
        kprint("Adding " #TEST_CATEGORY " tests... ");   \
        add_##TEST_CATEGORY##_tests();                   \
        kprint("Done!\n");                              \
    };

void add_tests()
{
    ADD_TESTS(hal);
    ADD_TESTS(awoostr);
}

void kernel_main()
{
    bool continue_booting = true;

    hal_init();
    badmalloc_init(kernel_end);
    kprint(AWOO_INFO "\r\n");

    add_tests();
    continue_booting = test_run_all();

    if (!continue_booting) {
        hal_test_fail_shutdown();
    }

    if (strcmp(AWOO_BUILD_TYPE, "TEST") == 0) {
        hal_hard_shutdown();
    }

    // Hooray, tests passed! Now to actually do something.
}
