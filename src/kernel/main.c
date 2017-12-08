#include <awoo.h>
#include <stdint.h>
#include <badmalloc.h>
#include <ktest.h>
#include <awoo/tests.h>

extern size_t *kernel_end;

#define ADD_TESTS(TEST_CATEGORY) { \
        kprint("Adding " #TEST_CATEGORY " tests... ");   \
        add_##TEST_CATEGORY##_tests();                   \
        kprint("Done!\n");                              \
    };

void kernel_main()
{
    hal_init();
    badmalloc_init(kernel_end);
    kprint(AWOO_INFO "\r\n");

    ADD_TESTS(hal);
    ADD_TESTS(awoostr);

    if (!test_run_all()) {
        hal_test_fail_shutdown();
    }

    if (AWOO_BUILD_TYPE_NUMBER == AWOO_TEST_BUILD) {
        hal_hard_shutdown();
    }

    // Hooray, tests passed! Now to actually do something.
}
