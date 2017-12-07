#ifndef KTEST_H
#define KTEST_H

#include <stddef.h>
#include <stdbool.h>
#include <badmalloc.h>

typedef struct {
	int status;
	const char *message;
} TestResult;

typedef struct TestCase_s {
	const char *name;
	TestResult* (*func) ();
	struct TestCase_s *next;
	struct TestCase_s *prev;
} TestCase;

void test_init();
TestResult *test_assert(char *code, bool result);
TestCase *test_add(const char *n, TestResult* (*fn)());
bool test_run_all();

#define TEST(NAME) test_add(#NAME, (TestResult* (*)())test_##NAME)

#define TEST_SUCCESS 0
#define TEST_FAILURE 1
#define TEST_FATAL   2
#define TEST_SKIP    3

#define kmalloc badmalloc
#define TEST_RETURN(STATUS, MESSAGE) TestResult *ret = (TestResult*)kmalloc(sizeof(TestResult)); \
                                     ret->status = STATUS;                                       \
                                     ret->message = MESSAGE;                                    \
                                     return ret;

#define TEST_ASSERT(CODE)   if (CODE) { \
                                TEST_RETURN(TEST_SUCCESS, #CODE);    \
                            } else {                                \
                                TEST_RETURN(TEST_FAILURE, #CODE);    \
                            }

#endif /* KTEST_H */
