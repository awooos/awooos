#include <tinker.h>
#include <stddef.h>
#include <kernel.h>
#include <ali/number.h>
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

size_t ran = 0;
size_t total = 0;
size_t passed = 0;
size_t failed = 0;
size_t skipped = 0;


static const char *test_status_messages[4] = {
    "Passed",
    "Failure",
    "Skipped",
    "Assertion failed",
};

void tinker_init(TinkerPrintFn *_printfn)
{
    tinker_print = _printfn;
}

void _tinker_add_test(const char *name, size_t (*function_ptr)())
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
        tinker_print(n_to_str(total + 1));
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
        tinker_print(n_to_str(line));
        tinker_print("\n");
    }
}

bool tinker_run_tests()
{
    size_t passed_assertions;

    tinker_print("\nRunning tests:\n\n");

    total = 0;

    for(size_t idx = 0; idx < last_test_index; idx++) {
        passed_assertions = test_cases[idx].func();
        ran++;
        total++;

        passed += passed_assertions;
        total += passed_assertions;
    }

    tinker_print("\n\n");

    tinker_print("Total tests: ");
    tinker_print(n_to_str(total));
    tinker_print("\n");

    tinker_print("     Passed: ");
    tinker_print(n_to_str(passed));
    tinker_print("\n");

    tinker_print("     Failed: ");
    tinker_print(n_to_str(failed));
    tinker_print("\n");

    tinker_print("    Skipped: ");
    tinker_print(n_to_str(skipped));
    tinker_print("\n\n");
    /*printf("Total tests: %i\n", ran);
      printf("     Passed: %i\n", passed);
      printf("     Failed: %i\n", failed);
      printf("    Skipped: %i\n\n", skipped);*/

    if (failed > 0) {
        return false;
    }

    return true;
}
