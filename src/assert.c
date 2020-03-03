#include <ali/number.h>
#include <stdio.h>
#include <assert.h>

void __ali_assert_fail(const char *expr, const char *file,
                        unsigned int line, const char *func)
{
    // TODO: Implement a significantly better version.
    fputs("???: ", stdout);
    fputs(file, stdout);
    fputs(":", stdout);
    print_number(line);
    fputs(": ", stdout);
    fputs(func, stdout);
    fputs("Assertion `", stdout);
    fputs(expr, stdout);
    fputs("' failed.", stdout);
}
