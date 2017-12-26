#include <awoo.h>
#include <stdint.h>
#include <badmalloc.h>
#include <ktest.h>
#include <awoo/tests.h>

#define ADD_TESTS(TEST_CATEGORY) { \
        kprint("Adding " #TEST_CATEGORY " tests... ");  \
        add_##TEST_CATEGORY##_tests();                  \
        kprint("Done!\n");                              \
    };

void kernel_main()
{
    hal_init();
    badmalloc_init();
    kprint(AWOO_INFO "\r\n");

    kprint("Compiled with ");
    kprint(hal_compiler_information());
    kprint("\r\n\r\n");

    hal_events_init();
    extern void hal_enable_interrupts();
    hal_enable_interrupts();

    kprint("\r\n");

    ADD_TESTS(hal);
    ADD_TESTS(badmalloc);
    ADD_TESTS(awoostr);

    if (!test_run_all()) {
        hal_test_fail_shutdown();
    }

    if (AWOO_BUILD_TYPE_NUMBER == AWOO_TEST_BUILD) {
        hal_hard_shutdown();
    }

    while(1){}

    // Hooray, tests passed! Now to actually do something.
    panic("Reached the end of the kernel!");
}
