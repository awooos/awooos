#include <tinker.h>

// TODO: Test handling of message, filename, line number.

void tinker_low_level_print_results(TinkerPrintFn *_print,
        unsigned long *_total, unsigned long *_passed,
        unsigned long *_failed, unsigned long *_skipped,
        int status, const char *message, const char *file, unsigned long line);

static unsigned long total = 0;
static unsigned long passed = 0;
static unsigned long failed = 0;
static unsigned long skipped = 0;

void print_results(int status, const char *message, const char *file, unsigned long line)
{
    tinker_low_level_print_results(0, &total, &passed, &failed, &skipped,
            status, message, file, line);
}

void fake_assert(int status)
{
    print_results(status, "Message", "file", 1);
}


void test_tinker_assert(void)
{
    // Initial test.
    tinker_assert(total == 0);
    tinker_assert(passed == 0);
    tinker_assert(failed == 0);
    tinker_assert(skipped == 0);

    // One success.
    fake_assert(TEST_SUCCESS);
    tinker_assert(total == 1);
    tinker_assert(passed == 1);
    tinker_assert(failed == 0);
    tinker_assert(skipped == 0);

    // One failure.
    fake_assert(TEST_FAILURE);
    tinker_assert(total == 2);
    tinker_assert(passed == 1);
    tinker_assert(failed == 1);
    tinker_assert(skipped == 0);

    // One skip.
    fake_assert(TEST_SKIP);
    tinker_assert(total == 3);
    tinker_assert(passed == 1);
    tinker_assert(failed == 1);
    tinker_assert(skipped == 1);

    // Two successes.
    fake_assert(TEST_SUCCESS);
    tinker_assert(total == 4);
    tinker_assert(passed == 2);
    tinker_assert(failed == 1);
    tinker_assert(skipped == 1);

    // Two failures.
    fake_assert(TEST_FAILURE);
    tinker_assert(total == 5);
    tinker_assert(passed == 2);
    tinker_assert(failed == 2);
    tinker_assert(skipped == 1);

    // Two skips.
    fake_assert(TEST_SKIP);
    tinker_assert(total == 6);
    tinker_assert(passed == 2);
    tinker_assert(failed == 2);
    tinker_assert(skipped == 2);
}

void add_tinker_assert_tests(void)
{
    tinker_add_test(tinker_assert);
}
