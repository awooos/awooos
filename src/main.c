#include <tinker.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

/*
 * Test suite for the AwooOS kernel.
 *
 * How to add a test:
 *    Assume for this example your test is named "cow"
 *
 *    size_t TestCow()
 *    {
 *       TEST_RETURN(status, message);
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

static TestCase test_cases[2048];

static size_t last_test_index = 0;

static size_t ran = 0;
static size_t total = 0;
static size_t passed = 0;
static size_t failed = 0;
static size_t skipped = 0;


static const char *test_status_messages[4] = {
    "Passed",
    "Failure",
    "Skipped",
    "Assertion failed",
};

// Hacktastic int-to-string function, so we don't need nonstandard
// functionality (e.g. tinker_uint_to_str()) or snprintf().
//
// If we can get an snprintf() that doesn't rely on malloc() into Ali,
// we should (in theory) be able to switch without hesitation.
//
// ASSUMPTION: number will never be larger than can fit in a uint64_t.
// NOTE: If the buffer is too small, the string gets truncated.
#define TINKER_UINT64_BUFSIZE 21 // <digits in uint64_t> + <1 byte for NULL>
static char uint_to_str_buffer[TINKER_UINT64_BUFSIZE] = {0};
char *tinker_uint_to_str(size_t n)
{
    char *buffer = uint_to_str_buffer;
    size_t radix = 10;

    // Set the entire buffer to NULL bytes.
    // (Inlined memset() to avoid dependencies.)
    for (size_t idx = 0; idx < TINKER_UINT64_BUFSIZE; idx++) {
        buffer[idx] = 0;
    }

    // Loop through the digits and add them in reverse order,
    // starting at the end of the string and working back.
    for (size_t idx = TINKER_UINT64_BUFSIZE - 1; idx > 0; idx--) {
        buffer[idx - 1] = "0123456789abcdef"[n % radix];
        n /= radix;
    }

    for (size_t idx = 0; idx < TINKER_UINT64_BUFSIZE; idx++) {
        // If the first char is _not_ zero, or the second char is NULL, stop.
        if (buffer[0] != '0' || buffer[1] == '\0') {
            break;
        }
        buffer++;
    }

    return buffer;
}

char *tinker_print(const char *string)
{
    return _tinker_print(string);
}

void _tinker_add_test(const char *name, size_t (*function_ptr)(void))
{
    size_t idx = last_test_index;

    strcpy(test_cases[idx].name, name);
    test_cases[idx].func = function_ptr;

    last_test_index += 1;
}

void _tinker_print_results(size_t status,
        const char *message, const char *file, size_t line)
{
    if(status == TEST_SUCCESS) {
        passed++;
    } else if (status == TEST_FAILURE || status == TEST_ASSERTION_FAILURE) {
        failed++;
    } else if (status == TEST_SKIP) {
        skipped++;
    }


    if(status == TEST_SUCCESS) {
        tinker_print(".");
    } else {
        tinker_print("\n");

        // X) <test name>
        tinker_print(tinker_uint_to_str(total + 1));
        tinker_print(") ");

        tinker_print(test_status_messages[status]);
        tinker_print(": ");

        tinker_print(test_cases[ran].name);
        tinker_print("\n");
        tinker_print("        ");

        tinker_print(message);
        tinker_print("\n");

        // Padding to line up with prior lines.
        tinker_print("   ");

        tinker_print("In ");
        tinker_print(file);
        tinker_print(":");
        tinker_print(tinker_uint_to_str(line));
        tinker_print("\n");
    }
}

bool tinker_run_tests(TinkerPrintFn *printfn_)
{
    _tinker_print = printfn_;

    tinker_print("\nRunning tests:\n\n");

    total = 0;

    for(size_t idx = 0; idx < last_test_index; idx++) {
        if (TINKER_VERBOSE) {
            tinker_print("\n- test_");
            tinker_print(test_cases[idx].name);
            tinker_print("()\n");
        }

        size_t passed_assertions = test_cases[idx].func();
        ran++;
        total++;

        if (TINKER_VERBOSE) {
            tinker_print("\n");
        }

        passed += passed_assertions;
        total += passed_assertions;
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
        return false;
    }

    return true;
}
