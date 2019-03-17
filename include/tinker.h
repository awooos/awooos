#ifndef TINKER_H
#define TINKER_H

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#ifndef TINKER_VERBOSE
#define TINKER_VERBOSE 0
#endif

typedef int (TinkerPrintFn)(const char *string);
static TinkerPrintFn *_tinker_print = NULL;

typedef struct TestCase_s {
    char name[1024];
    size_t (*func) (void);
} TestCase;

void _tinker_add_test(const char *n, size_t (*fn)(void));
bool tinker_run_tests(TinkerPrintFn *printfn_);
void _tinker_print_results(size_t status,
        const char *message, const char *file, size_t line);

char *tinker_print(const char *string);

#define tinker_add_test(NAME) _tinker_add_test(#NAME, test_##NAME)

#define TEST_SUCCESS            0
#define TEST_FAILURE            1
#define TEST_SKIP               2
#define TEST_ASSERTION_FAILURE  3

#define TEST_RETURN2(STATUS, MESSAGE, PASSED_ASSERTIONS)            \
    _tinker_print_results(STATUS, MESSAGE, __FILE__, __LINE__);    \
    return PASSED_ASSERTIONS

#define TEST_RETURN(STATUS, MESSAGE) TEST_RETURN2(STATUS, MESSAGE, 0)

#define TEST_HAS_ASSERTIONS() size_t passed_assertions = 0;

#define TEST_ASSERT(CODE)   if (CODE) {                             \
    passed_assertions += 1;             \
    if (TINKER_VERBOSE) { \
        tinker_print("-- "); tinker_print(#CODE); tinker_print("\n"); \
    } else { \
        tinker_print(".");                  \
    } \
} else {                                \
    TEST_RETURN2(TEST_ASSERTION_FAILURE,\
#CODE, passed_assertions);      \
}

#define TEST_ASSERTIONS_RETURN()    TEST_RETURN2(TEST_SUCCESS, "All assertions passed.", passed_assertions)

#endif
