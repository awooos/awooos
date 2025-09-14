#ifndef TINKER_H
#define TINKER_H

// `tinker_verbose` is considered part of the public API.
#ifndef TINKER_VERBOSE
/// Specifies whether Tinker should use verbose output.
/// 0 = normal, 1 = verbose.
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

void tinker_add_test_with_name(TinkerTestcaseFn *func, const char *name);
void tinker_print_results(int status,
        const char *message, const char *file, unsigned long line);
int tinker_low_level_assert(int success,
        const char *code, const char *file, unsigned long line);

enum tinker_test_result {
    TEST_SUCCESS,
    TEST_FAILURE,
    TEST_SKIP,
};


// Everything below here is part of the public API.

/// Run the test suite. Make sure all tests are added using #tinker_add_test first.
///
/// @p putcharfn is a pointer to a function with the same signature as
/// `putchar`:
///     int putchar(int c)
///
/// @returns 1 on success, 0 on failure
int tinker_run_tests(TinkerPutcharFn *putcharfn);

/// @def tinker_add_test(NAME)
/// Adds function `test_NAME()` as a test, with name `NAME`.
#define tinker_add_test(NAME) tinker_add_test_with_name(test_##NAME, #NAME)

/// @def tinker_assert(CODE)
/// Assert th at `CODE` returns a truthy value.
/// On failure, prints failure information and returns immediately.
#define tinker_assert(CODE) do { if (!tinker_low_level_assert((CODE), #CODE, __FILE__, __LINE__)) { return; } } while(0)

/// @def tinker_pass()
/// Indicate that a test passed.
#define tinker_pass()        tinker_print_results(TEST_SUCCESS, "Success.", __FILE__, __LINE__)

/// @def tinker_fail(MESSAGE)
/// Indicate that a test failed. Prints failure information, using `MESSAGE`
/// as the description of the problem.
///
/// NOTE: If you call this in the middle of a function it _won't_ return
/// immediately. You'll need to explicitly add `return;` afterwards.
#define tinker_fail(MESSAGE) tinker_print_results(TEST_FAILURE, MESSAGE,    __FILE__, __LINE__)

/// @def tinker_skip(MESSAGE)
/// Indicate that a test is skipped. Prints information about what was skipped,
/// using `MESSAGE` as the reason for skipping it.
///
/// NOTE: If you call this in the middle of a function it _won't_ return
/// immediately. You'll need to explicitly add `return;` afterwards.
#define tinker_skip(MESSAGE) tinker_print_results(TEST_SKIP,    MESSAGE,    __FILE__, __LINE__)

#endif
