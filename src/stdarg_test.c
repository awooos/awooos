#include <tinker.h>
#include <stdarg.h>

void _test_args(int num_args, ...) {
    va_list ap;
    int i;

    va_start(ap, num_args);
    for (i = 1; i <= num_args; i++) {
        int arg = va_arg(ap, int);
        tinker_assert(arg == i);
    }
    va_end(ap);

    tinker_assert((i - 1) == num_args);
}

void test_ali_stdarg_assertions(void) {
    _test_args(/* numArgs = */ 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    _test_args(/* numArgs = */ 3, 1, 2, 3);
    _test_args(/* numArgs = */ 1, 1);
    _test_args(/* numArgs = */ 0);
}

void add_ali_stdarg_tests(void) {
    tinker_add_test(ali_stdarg_assertions);
}
