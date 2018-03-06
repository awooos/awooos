#ifndef TINKER_H
#define TINKER_H

#include <stddef.h>
#include <stdbool.h>
#include <kernel.h>
#include <string.h>
#include <stdlib.h>

typedef int (TinkerPrintFn)(const char *string);
static const TinkerPrintFn *tinker_print = NULL;

typedef struct TestCase_s {
    char name[1024];
    size_t (*func) ();
} TestCase;

void tinker_init(TinkerPrintFn *_printfn);
void _tinker_add_test(const char *n, size_t (*fn)());
bool tinker_run_tests();
void _tinker_print_results(size_t status,
        const char *message, const char *file, size_t line);

#define tinker_add_test(NAME) _tinker_add_test(#NAME, test_##NAME)

#define TEST_SUCCESS            0
#define TEST_FAILURE            1
#define TEST_SKIP               2
#define TEST_ASSERTION_FAILURE  3

#define _TEST_RETURN(STATUS, MESSAGE, PASSED_ASSERTIONS)            \
    _tinker_print_results(STATUS, MESSAGE, __FILE__, __LINE__);    \
    return PASSED_ASSERTIONS

#define TEST_RETURN(STATUS, MESSAGE) _TEST_RETURN(STATUS, MESSAGE, 0)

#define TEST_HAS_ASSERTIONS() size_t passed_assertions = 0;

#define TEST_ASSERT(CODE)   if (CODE) {                             \
    passed_assertions += 1;             \
    tinker_print(".");                  \
} else {                                \
    _TEST_RETURN(TEST_ASSERTION_FAILURE,\
#CODE, passed_assertions);      \
}

#define TEST_ASSERTIONS_RETURN()    _TEST_RETURN(TEST_SUCCESS, "All assertions passed.", passed_assertions)

#endif
