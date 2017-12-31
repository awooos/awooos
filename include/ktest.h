#ifndef KTEST_H
#define KTEST_H

#include <stddef.h>
#include <stdbool.h>
#include <kernel.h>
#include <badmalloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int status;
	char *message;
    char *file;
    int line;
    size_t passed_assertions;
} TestResult;

typedef struct TestCase_s {
	char *name;
	TestResult* (*func) ();
	struct TestCase_s *next;
	struct TestCase_s *prev;
} TestCase;

void test_init();
TestCase *test_add(const char *n, TestResult* (*fn)());
bool test_run_all();

#define TEST(NAME) test_add(#NAME, (TestResult* (*)())test_##NAME)

#define TEST_SUCCESS            0
#define TEST_FAILURE            1
#define TEST_SKIP               2
#define TEST_ASSERTION_FAILURE  3

#define kmalloc badmalloc
#define _TEST_RETURN(STATUS, MESSAGE, PASSED_ASSERTIONS) \
        TestResult *ret = (TestResult*)kmalloc(sizeof(TestResult));         \
        memset(ret, 0, sizeof(TestResult));                                 \
        char *__msg = (char*)kmalloc(sizeof(char) * strlen(MESSAGE));       \
        strcpy(__msg, MESSAGE);                                             \
        char *__file = (char*)kmalloc(sizeof(char) * strlen("" __FILE__));  \
        strcpy(__file, __FILE__);                                           \
        ret->status = STATUS;                                               \
        ret->message = __msg;                                               \
        ret->passed_assertions = PASSED_ASSERTIONS;                         \
        ret->file = __file;                                                 \
        ret->line = __LINE__;                                               \
        return ret;

#define TEST_RETURN(STATUS, MESSAGE) _TEST_RETURN(STATUS, MESSAGE, 0)

#define TEST_HAS_ASSERTIONS() size_t passed_assertions = 0;

#define TEST_ASSERT(CODE)   if (CODE) {                                     \
                                passed_assertions += 1;                     \
                                kprint(".");                                \
                            } else {                                        \
                                _TEST_RETURN(TEST_ASSERTION_FAILURE, #CODE, passed_assertions)  \
                            }                                               \

#define TEST_ASSERTIONS_RETURN()    _TEST_RETURN(TEST_SUCCESS, "All assertions passed.", passed_assertions)

#endif /* KTEST_H */
