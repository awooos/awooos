#include <awoo/build_info.h>
#include <awoo/tests.h>
#include <ktest.h>
#include <eventually.h>

#define ADD_TESTS(TEST_CATEGORY) { \
        kprint("Adding " #TEST_CATEGORY " tests... ");  \
        add_##TEST_CATEGORY##_tests();                  \
        kprint("Done!\n");                              \
    };

void tests_shutdown(bool test_succeeded)
{
    if (test_succeeded) {
        eventually_event_trigger_immediate("HAL shutdown hard", NULL, 0);
    } else {
        eventually_event_trigger_immediate("HAL shutdown test fail", NULL, 0);
    }
}

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
        tests_shutdown(test_status);
        break;
    case 2:
        test_flail_intentional_panic();
        tests_shutdown(true);
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
