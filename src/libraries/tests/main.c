#include <awoo/build_info.h>
#include <awoo/tests.h>
#include <ktest.h>
#include <ali/event.h>
#include <dmm.h>

#define ADD_TESTS(TEST_CATEGORY) { \
        kprint("Adding " #TEST_CATEGORY " tests... ");  \
        add_##TEST_CATEGORY##_tests();                  \
        kprint("Done!\n");                              \
    };

void tests_shutdown_success() {
    event_trigger("HAL shutdown hard", NULL, 0);
}

void tests_shutdown_failure()
{
    event_trigger("HAL shutdown test fail", NULL, 0);
}

void run_tests()
{
    bool all_tests_passed;

    ADD_TESTS(hal);
    ADD_TESTS(ali);
    ADD_TESTS(dmm);

    all_tests_passed = test_run_all();

    // If it's not a test build, this is all we run.
    if (AWOO_BUILD_TYPE_NUMBER != AWOO_TEST_BUILD) {
        return;
    }

    // If a test failed, just shut down.
    if (!all_tests_passed) {
        tests_shutdown_failure();
    }

    // This doesn't catch all failures, but it'll catch unintentional
    // infinite loops by causing the CI build to time out.
    test_flail_intentional_panic();

    // If we get this far, we assume all of the tests passed.
    tests_shutdown_success();
}

void tests_register_events()
{
    event_watch("tests run", run_tests);
}
