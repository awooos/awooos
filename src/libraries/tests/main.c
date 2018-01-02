#include <awoo/build_info.h>
#include <awoo/tests.h>
#include <ktest.h>
#include <eventually.h>

#define ADD_TESTS(TEST_CATEGORY) { \
        kprint("Adding " #TEST_CATEGORY " tests... ");  \
        add_##TEST_CATEGORY##_tests();                  \
        kprint("Done!\n");                              \
    };

void run_tests()
{
    bool test_status;

    ADD_TESTS(hal);
    ADD_TESTS(libc);
    ADD_TESTS(awoostr);

    test_status = test_run_all();

    switch (AWOO_TEST_SECTION) {
    case 0:
        // Not a test build.
        break;
    case 1:
        hal_test_shutdown(test_status);
        break;
    case 2:
        run_panic_test();
        break;
    default:
        panic("Encountered unknown test section!");
        break;
    }
}

void tests_register_events()
{
    eventually_event_watch("tests run", run_tests);
}
