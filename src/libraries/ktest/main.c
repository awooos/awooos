#include <ktest.h>
#include <stddef.h>
#include <badmalloc.h>
#include <kernel.h>
#include <awoostr.h>
#include <string.h>

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
    "PASS",
    "FAIL",
    "FATAL",
    "SKIP",
};

TestCase *test_add(const char *name, TestResult* (*function_ptr)())
{
    TestCase *test_case = (TestCase*)badmalloc(sizeof(TestCase));
    TestCase *tmp;

    memset(test_case, 0, sizeof(TestCase));

    test_case->name = name;
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

int test_run(size_t ran, TestCase *test)
{
    TestResult *ret;

    ret = test->func();

    if(ret->status == TEST_SUCCESS) {
        kprint(".");
    } else {
        if (ran > 0) {
            kprint("\n");
        }

        kprint(test_status_messages[ret->status]);
        kprint(": ");
        kprint(test->name);
        kprint(": ");
        kprint(ret->message);
        kprint("\n");
    }

    return ret->status;
}

bool test_run_all()
{
    TestCase *test;
    int status;
    size_t ran = 0;
    size_t passed = 0;
    size_t failed = 0;
    size_t fatal  = 0;
    size_t skipped = 0;

    kprint("\nRunning tests:\n\n");

    for(test = first_test; test != NULL; test = test->next) {
        status = test_run(ran, test);
        ran++;

        if(status == TEST_SUCCESS) {
            passed++;
        } else if (status == TEST_FAILURE) {
            failed++;
        } else if (status == TEST_FATAL) {
            failed++;
            fatal++;
        } else if (status == TEST_SKIP) {
            skipped++;
        }
    }

    kprint("Total tests: ");
    kprint(str(ran));
    kprint("\n");

    kprint("     Passed: ");
    kprint(str(passed));
    kprint("\n");

    kprint("     Failed: ");
    kprint(str(failed));
    kprint("\n");

    kprint("      Fatal: ");
    kprint(str(fatal));
    kprint("\n");

    kprint("    Skipped: ");
    kprint(str(skipped));
    kprint("\n\n");
    /*printf("Total tests: %i\n", ran);
      printf("     Passed: %i\n", passed);
      printf("     Failed: %i\n", failed);
      printf("      Fatal: %i\n", fatal);
      printf("    Skipped: %i\n\n", skipped);*/

    if (fatal > 0) {
        kprint("Fatal error encountered; not booting.\n");
        return false;
    } else if (failed > passed) {
        kprint("Majority of tests failed; not booting.\n");
        return false;
    }

    return true;
}
