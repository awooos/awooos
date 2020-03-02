#ifndef TINKER_H
#define TINKER_H

#ifndef TINKER_VERBOSE
/// 0 = normal
/// 1 = verbose
static unsigned int tinker_verbose = 0;
#else
static unsigned int tinker_verbose = 1;
#endif

typedef int (TinkerPutcharFn)(int c);
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

int _tinker_assert(int success, const char *code);

#define tinker_add_test(NAME) _tinker_add_test(test_##NAME, #NAME)

enum tinker_test_result {
    TEST_SUCCESS,
    TEST_FAILURE,
    TEST_SKIP,
    TEST_ASSERTION_FAILURE,
};

#define TINKER_FINISH(STATUS, MESSAGE) _tinker_print_results(STATUS, MESSAGE, __FILE__, __LINE__)

#define tinker_assert(CODE) if (!_tinker_assert((CODE), #CODE)) { return; }

#define TINKER_ASSERTIONS_FINISH() TINKER_FINISH(TEST_SUCCESS, "All assertions passed.")

#endif
