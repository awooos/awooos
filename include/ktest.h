#ifndef KTEST_H
#define KTEST_H

#include <stddef.h>
#include <stdbool.h>
#include <badmalloc.h>

typedef struct {
	int status;
	char *message;
    char *file;
    int line;
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
#define TEST_FATAL              2
#define TEST_SKIP               3
#define TEST_ASSERTION_FAILURE  4

#include <kernel.h>
#define kmalloc badmalloc
#define TEST_RETURN(STATUS, MESSAGE) TestResult *ret = (TestResult*)kmalloc(sizeof(TestResult));        \
                                     memset(ret, 0, sizeof(TestResult));                                \
                                     char *__msg = (char*)kmalloc(sizeof(char) * strlen(MESSAGE));      \
                                     strcpy(__msg, MESSAGE);                                            \
                                     char *__file = (char*)kmalloc(sizeof(char) * strlen("" __FILE__)); \
                                     strcpy(__file, __FILE__);                                          \
                                     ret->status = STATUS;                                              \
                                     ret->message = __msg;                                              \
                                     ret->file = __file;                                                \
                                     ret->line = __LINE__;                                              \
                                     return ret;


#define TEST_ASSERT(CODE)   if (CODE) {                                     \
                                TEST_RETURN(TEST_SUCCESS, #CODE);           \
                            } else {                                        \
                                TEST_RETURN(TEST_ASSERTION_FAILURE, #CODE)  \
                            }                                               \

#endif /* KTEST_H */
