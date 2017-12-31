#include <ktest.h>
#include <stddef.h>
#include <badmalloc.h>
#include <kernel.h>
#include <awoostr.h>
#include <string.h>
#include <stdlib.h>

/*
 * Test suite for the AwooOS kernel.
 * 
 * How to add a test:
 *    Assume for this example your test is named "cow"
 * 
 *    TestResult *TestCow()
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

static TestCase *first_test = NULL;
static TestCase *last_test = NULL;

static const char *test_status_messages[4] = {
    "Passed",
    "Failure",
    "Skipped",
    "Assertion failed",
};

TestCase *test_add(const char *name, TestResult* (*function_ptr)())
{
    extern void *kmalloc_int(unsigned int size, unsigned int flags);
    TestCase *test_case = (TestCase*)kmalloc_int(sizeof(TestCase), 0);

    memset(test_case, 0, sizeof(TestCase));

    char *name_ = (char*)kmalloc_int(sizeof(char) * strlen(name), 0);
    strcpy(name_, name);
    test_case->name = name_;
    test_case->func = function_ptr;

    if(first_test == NULL) {
        first_test = test_case;
        first_test->prev = NULL;
        first_test->next = NULL;
    }

    if (last_test == NULL) {
        last_test = first_test;
    } else if (last_test != NULL) {
        last_test->next = test_case;
        last_test->prev = last_test;
        last_test = test_case;
        last_test->next = NULL;
    }

    return test_case;
}

TestResult *test_run(size_t ran, TestCase *test)
{
    TestResult *ret;
    ret = test->func();

    if(ret->status == TEST_SUCCESS) {
        kprint(".");
    } else {
        kprint("\n");

        // X) <test name>
        kprint(str(ran + 1));
        kprint(") ");

        kprint(test_status_messages[ret->status]);
        kprint(": ");

        kprint(test->name);
        kprint("\n");
        kprint("        ");

        kprint(ret->message);
        kprint("\n");

        // Padding to line up with prior lines.
        kprint("   ");

        kprint("In ");
        kprint(ret->file);
        kprint(":");
        kprint(str(ret->line));
        kprint("\n");
    }

    return ret;
}

bool test_run_all()
{
    TestCase *test;
    TestResult *ret;
    int status;
    size_t total = 0;
    size_t passed = 0;
    size_t failed = 0;
    size_t skipped = 0;

    kprint("\nRunning tests:\n\n");

    for(test = first_test; test != NULL; test = test->next) {
        ret = test_run(total, test);
        status = ret->status;
        total++;

        passed += ret->passed_assertions;
        total += ret->passed_assertions;

        if(status == TEST_SUCCESS) {
            passed++;
        } else if (status == TEST_FAILURE || status == TEST_ASSERTION_FAILURE) {
            failed++;
        } else if (status == TEST_SKIP) {
            skipped++;
        }
    }

    kprint("\n\n");

    kprint("Total tests: ");
    kprint(str(total));
    kprint("\n");

    kprint("     Passed: ");
    kprint(str(passed));
    kprint("\n");

    kprint("     Failed: ");
    kprint(str(failed));
    kprint("\n");

    kprint("    Skipped: ");
    kprint(str(skipped));
    kprint("\n\n");
    /*printf("Total tests: %i\n", ran);
      printf("     Passed: %i\n", passed);
      printf("     Failed: %i\n", failed);
      printf("    Skipped: %i\n\n", skipped);*/

    if (failed > 0) {
        kprint("Encountered failing tests; not booting.\n");
        return false;
    }

    return true;
}
