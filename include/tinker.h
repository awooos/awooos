#ifndef TINKER_H
#define TINKER_H

#ifndef TINKER_VERBOSE
/// 0 = normal
/// 1 = verbose
#define TINKER_VERBOSE 0
#endif

typedef int (TinkerPutcharFn)(int c);
// This would normally be set to NULL, but this avoids needing that defined.
static TinkerPutcharFn *_tinker_putchar = 0;

typedef void (TinkerTestcaseFn)(void);

#define TINKER_TEST_NAME_BUFFER_LENGTH 1024
typedef struct TestCase_s {
    char name[TINKER_TEST_NAME_BUFFER_LENGTH];
    TinkerTestcaseFn *func;
} TestCase;

void _tinker_add_test(TinkerTestcaseFn *func, const char *name);
int tinker_run_tests(TinkerPutcharFn *putcharfn);
void _tinker_print_results(int status,
        const char *message, const char *file, unsigned long line);

char *tinker_print(const char *string);

void _tinker_assert(int success, const char *code);

#define tinker_add_test(NAME) _tinker_add_test(test_##NAME, #NAME)

enum tinker_test_result {
    TEST_SUCCESS,
    TEST_FAILURE,
    TEST_SKIP,
    TEST_ASSERTION_FAILURE,
};

#define TEST_RETURN(STATUS, MESSAGE) _tinker_print_results(STATUS, MESSAGE, __FILE__, __LINE__)


#define tinker_assert(CODE) _tinker_assert((CODE), #CODE)
// For backwards-compatibility until the refactor is properly done.
#define TEST_ASSERT(CODE) tinker_assert(CODE)

#define TEST_ASSERTIONS_RETURN() _tinker_print_results(TEST_SUCCESS, "All assertions passed.", __FILE__, __LINE__)

#endif
