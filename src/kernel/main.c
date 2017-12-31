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

    switch (AWOO_TEST_SECTION) {
    case 0:
        // Not a test build.
        break;
    case 1:
        hal_test_shutdown(test_run_all());
        break;
    case 2:
        test_panic("Successful kernel panic!");
        break;
    default:
        panic("Unknown test section!");
        break;
    }

    //while(1){}

    // Hooray, tests passed! Now to actually do something.
    panic("Reached the end of the kernel!");
}
