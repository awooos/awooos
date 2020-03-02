#include <tinker.h>

/*
 * Test framework with very few dependencies.
 * Built for kernel development, theoretically usable for other things.
 *
 * How to add a test:
 *    Assume for this example your test is named "cow"
 *
 *    void test_cow()
 *    {
 *       tinker_finish(status, message);
 *    }
 *
 *    status is one of the TEST_* variables in include/kernel/colpa/test.h:
 *     - TEST_SUCCESS (test passed)
 *     - TEST_FAILURE (test failed, nonfatal)
 *     - TEST_FATAL   (test failed, fatal - will not let the system boot)
 *
 *    message is a string or NULL.
 *
 *    If message is NULL, no explanatory message is printed.
 */

#ifndef TINKER_MAX_TESTS
/// The number of tests to (statically) allocate space for.
/// Can be overridden by defining TINKER_MAX_TESTS at compile time.
#   define TINKER_MAX_TESTS 2048
#endif

// This would normally be set to NULL, but this avoids needing that defined.
static TinkerPutcharFn *_tinker_putchar = 0;

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
char *tinker_print(const char *string)
{
    for (char *s = (char*)string; *s; s++) {
        _tinker_putchar(*s);
    }
    return (char*)string;
}


/// Adds a test to the test suite.
///
/// You probably want tinker_add_test(name), which is equivalent to
/// _tinker_add_test(test_name, "name").
void _tinker_add_test(TinkerTestcaseFn *func, const char *name)
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


// Prints the results of a test.
/// @private
void _tinker_print_results(int status,
        const char *message, const char *file, unsigned long line)
{
    if(status == TEST_SUCCESS) {
        passed++;
    } else if (status == TEST_FAILURE) {
        failed++;
    } else if (status == TEST_SKIP) {
        skipped++;
    }


    if(status == TEST_SUCCESS) {
        // If we get to this branch, the test passed.

        // If `tinker_verbose` is 0, we print a dot (".") here.
        // Otherwise, we print info in `tinker_run_tests()`.
        if (tinker_verbose == 0) {
            tinker_print(".");
        }
    } else {
        // If we get to this branch, the test failed.

        // If the last test passed and `tinker_verbose` is zero, a newline
        // avoids printing the message after a long sequence of dots
        // (from passed tests).
        //
        // Otherwise, a newline helps break up large chunks of text to
        // improve readability.
        tinker_print("\n");

        // "<test number>) "
        tinker_print(tinker_uint_to_str(total + 1));
        tinker_print(") ");

        // "<test status message>: <test name>\n"
        tinker_print(test_status_messages[status]);
        tinker_print(": ");
        tinker_print(test_cases[ran].name);
        tinker_print("\n");

        // "        <message>\n"
        tinker_print("        ");
        tinker_print(message);
        tinker_print("\n");

        // "   In <filename>:<line number>\n"
        tinker_print("   ");
        tinker_print("In ");
        tinker_print(file);
        tinker_print(":");
        tinker_print(tinker_uint_to_str(line));
        tinker_print("\n");
    }
}

int _tinker_assert(int success,
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
        _tinker_print_results(TEST_FAILURE, code, file, line);
        return 0;
    }
}

/// Run the test suite.
///
/// `putcharfn` is a pointer to a function with the same signature as
/// `putchar`:
///     int putchar(int c)
///
/// @returns 1 on success, 0 on failure
int tinker_run_tests(TinkerPutcharFn *putcharfn)
{
    _tinker_putchar = putcharfn;

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
        total++;

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
