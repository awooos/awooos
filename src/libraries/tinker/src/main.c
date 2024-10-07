#include <tinker.h>

/* @file main.c
 *
 * Test framework that just needs a C11 compiler and a pointer to a
 * putchar()-compatible function.
 *
 * How to add a test:
 *
 *    void test_cow()
 *    {
 *        if (moo()) {
 *            tinker_pass();
 *        } else {
 *            tinker_fail("Explain the failure here.");
 *        }
 *    }
 *
 * See tinker.h for detailed API documentation.
 */

#ifndef TINKER_MAX_TESTS
/// The number of tests to (statically) allocate space for.
/// Can be overridden by defining TINKER_MAX_TESTS at compile time.
#   define TINKER_MAX_TESTS 2048
#endif

// This would normally be set to NULL, but this avoids needing that defined.
static TinkerPutcharFn *tinker_putchar = 0;

static TestCase test_cases[TINKER_MAX_TESTS];

static unsigned long last_test_index = 0;

static unsigned long ran = 0;
static unsigned long total = 0;
static unsigned long passed = 0;
static unsigned long failed = 0;
static unsigned long skipped = 0;

// Text representations of test states.
static const char *test_status_messages[4] = {
    "Passed",
    "Failure",
    "Skipped",
    "Assertion failed",
};

// Hacktastic int-to-string function, so we don't need nonstandard
// functionality or snprintf().
//
// ASSUMPTION: number will never be larger than can fit in a uint64_t.
// NOTE: If the buffer is too small, the string gets truncated.
/// @private
#define TINKER_UINT64_BUFSIZE 21 // <digits in uint64_t> + <1 byte for NULL>
static char uint_to_str_buffer[TINKER_UINT64_BUFSIZE] = {0};
char *tinker_uint_to_str(unsigned long n)
{
    char *buffer = uint_to_str_buffer;
    unsigned long radix = 10;

    // Set the entire buffer to NULL bytes.
    // (Inlined memset() to avoid dependencies.)
    for (unsigned long idx = 0; idx < TINKER_UINT64_BUFSIZE; idx++) {
        buffer[idx] = 0;
    }

    // Loop through the digits and add them in reverse order,
    // starting at the end of the string and working back.
    for (unsigned long idx = TINKER_UINT64_BUFSIZE - 1; idx > 0; idx--) {
        buffer[idx - 1] = "0123456789abcdef"[n % radix];
        n /= radix;
    }

    for (unsigned long idx = 0; idx < TINKER_UINT64_BUFSIZE; idx++) {
        // If the first char is _not_ zero, or the second char is NULL, stop.
        if (buffer[0] != '0' || buffer[1] == '\0') {
            break;
        }
        buffer++;
    }

    return buffer;
}
// Undefine constant which was only used to simplify things above.
#undef TINKER_UINT64_BUFSIZE


// Print a string, using the putchar()-equivalent passed to tinker_run_tests().
/// @private
void tinker_print(const char *string)
{
    for (char *s = (char*)string; *s; s++) {
        tinker_putchar(*s);
    }
}


/// Adds a test to the test suite.
///
/// You probably want tinker_add_test(name), which is equivalent to
/// tinker_add_test_with_name(test_name, "name").
void tinker_add_test_with_name(TinkerTestcaseFn *func, const char *name)
{
    unsigned long idx = last_test_index;

    unsigned long i;
    for (i = 0; i <= TINKER_TEST_NAME_BUFFER_LENGTH; i++) {
        if (i == TINKER_TEST_NAME_BUFFER_LENGTH && name[i]) {
            tinker_print("\n\n!!! ERROR: _tinker_add_test(): name is too long, and will be truncated.\n\n");
        }

        test_cases[idx].name[i] = name[i];

        if (!name[i]) {
            break;
        }
    }
    test_cases[idx].name[i] = 0;
    test_cases[idx].func = func;

    last_test_index += 1;
}


/// Prints the results of a test. Used internally by tinker_print_results()
/// and for tests.
///
/// @param[in]  _print   Either a pointer `tinker_print()` or NULL.
/// @param[out]  _total  A pointer to an accumulator for number of total tests.
/// @param[out] _passed  A pointer to an accumulator for number of passed tests.
/// @param[out] _failed  A pointer to an accumulator for number of failed tests.
/// @param[out] _skipped A pointer to an accumulator for number of skipped tests.
/// @param[in]  status   One of TEST_SUCCESS, TEST_FAILURE, or TEST_SKIPPED.
/// @param[in]  message  A string explaining the test results.
/// @param[in]  file     The file the relevant test is in.
/// @param[in]  line     The line the relevant test is on.
///
/// @private
void tinker_low_level_print_results(TinkerPrintFn *_print,
        unsigned long *_total, unsigned long *_passed,
        unsigned long *_failed, unsigned long *_skipped,
        int status, const char *message, const char *file, unsigned long line)
{
    (*_total)++;
    if(status == TEST_SUCCESS) {
        (*_passed)++;
    } else if (status == TEST_FAILURE) {
        (*_failed)++;
    } else if (status == TEST_SKIP) {
        (*_skipped)++;
    }

    // In normal usage, a valid pointer is provided to _print().
    // If _print is 0/NULL, we're running the test suite, and don't want
    // to print anything.
    if (!_print) {
        return;
    }

    if(status == TEST_SUCCESS) {
        // If we get to this branch, the test passed.

        // If `tinker_verbose` is 0, we print a dot (".") here.
        // Otherwise, we print info in `tinker_run_tests()`.
        if (tinker_verbose == 0) {
            _print(".");
        }
    } else {
        // If we get to this branch, the test failed.

        // If the last test passed and `tinker_verbose` is zero, a newline
        // avoids printing the message after a long sequence of dots
        // (from passed tests).
        //
        // Otherwise, a newline helps break up large chunks of text to
        // improve readability.
        _print("\n");

        // "<test number>) "
        _print(tinker_uint_to_str((*_total) + 1));
        _print(") ");

        // "<test status message>: <test name>\n"
        _print(test_status_messages[status]);
        _print(": ");
        _print(test_cases[ran].name);
        _print("\n");

        // "        <message>\n"
        _print("        ");
        _print(message);
        _print("\n");

        // "   In <filename>:<line number>\n"
        _print("   ");
        _print("In ");
        _print(file);
        _print(":");
        _print(tinker_uint_to_str(line));
        _print("\n");
    }
}

/// Prints the results of a test.
///
/// @param[in]  status   One of TEST_SUCCESS, TEST_FAILURE, or TEST_SKIPPED.
/// @param[in]  message  A string explaining the test results.
/// @param[in]  file     The file the relevant test is in.
/// @param[in]  line     The line the relevant test is on
///
/// @private
void tinker_print_results(int status,
        const char *message, const char *file, unsigned long line)
{
    tinker_low_level_print_results(&tinker_print,
            &total, &passed, &failed, &skipped,
            status, message, file, line);
}

/// Asserts that an expression returns a truthy value.
/// You probably want the tinker_assert() macro instead.
///
/// @param[in] success  Whether the assertion passed.
/// @param[in] code     A string representation of the code.
/// @param[in] file     The file the assertion is in (likely __FILE__).
/// @param[in] line     The line the assertion is on (likely __LINE__).
///
/// @private
int tinker_low_level_assert(int success,
        const char *code, const char *file, unsigned long line)
{
    if (success) {
        total++;
        passed++;
        if (tinker_verbose == 0) {
            tinker_print(".");
        } else {
            tinker_print("-- ");
            tinker_print(code);
            tinker_print("\n");
        }
        return 1;
    } else {
        tinker_print_results(TEST_FAILURE, code, file, line);
        return 0;
    }
}

// See tinker.h for usage information.
int tinker_run_tests(TinkerPutcharFn *putcharfn)
{
    tinker_putchar = putcharfn;

    tinker_print("\nRunning tests:\n\n");

    total = 0;

    for(unsigned long idx = 0; idx < last_test_index; idx++) {
        if (tinker_verbose != 0) {
            tinker_print("- test_");
            tinker_print(test_cases[idx].name);
            tinker_print("()\n");
        }

        test_cases[idx].func();

        ran++;

        if (tinker_verbose != 0) {
            tinker_print("\n");
        }
    }

    tinker_print("\n\n");

    tinker_print("Total tests: ");
    tinker_print(tinker_uint_to_str(total));
    tinker_print("\n");

    tinker_print("     Passed: ");
    tinker_print(tinker_uint_to_str(passed));
    tinker_print("\n");

    tinker_print("     Failed: ");
    tinker_print(tinker_uint_to_str(failed));
    tinker_print("\n");

    tinker_print("    Skipped: ");
    tinker_print(tinker_uint_to_str(skipped));
    tinker_print("\n\n");

    if (failed > 0) {
        return 0;
    }

    return 1;
}
