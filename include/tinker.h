#ifndef TINKER_H
#define TINKER_H

// `tinker_verbose` is considered part of the public API.
#ifndef TINKER_VERBOSE
/// 0 = normal
/// 1 = verbose
static unsigned int tinker_verbose = 0;
#else
static unsigned int tinker_verbose = 1;
#endif

typedef void (TinkerPrintFn)(const char *string);
typedef int (TinkerPutcharFn)(int c);
typedef void (TinkerTestcaseFn)(void);

#define TINKER_TEST_NAME_BUFFER_LENGTH 1024
typedef struct TestCase_s {
    char name[TINKER_TEST_NAME_BUFFER_LENGTH];
    TinkerTestcaseFn *func;
} TestCase;

void _tinker_add_test(TinkerTestcaseFn *func, const char *name);
void _tinker_print_results(int status,
        const char *message, const char *file, unsigned long line);
int _tinker_assert(int success,
        const char *code, const char *file, unsigned long line);

enum tinker_test_result {
    TEST_SUCCESS,
    TEST_FAILURE,
    TEST_SKIP,
};


// Everything below here is part of the public API.

int tinker_run_tests(TinkerPutcharFn *putcharfn);

#define tinker_add_test(NAME) _tinker_add_test(test_##NAME, #NAME)

#define tinker_assert(CODE) if (!_tinker_assert((CODE), #CODE, __FILE__, __LINE__)) { return; }

#define tinker_pass()        _tinker_print_results(TEST_SUCCESS, "Success.", __FILE__, __LINE__)
#define tinker_fail(MESSAGE) _tinker_print_results(TEST_FAILURE, MESSAGE,    __FILE__, __LINE__)
#define tinker_skip(MESSAGE) _tinker_print_results(TEST_SKIP,    MESSAGE,    __FILE__, __LINE__)

#endif
