#include <assert.h>

void __ali_assert_fail(const char *expr, const char *file,
                        unsigned int line, const char *func)
{
    // TODO: Implement a significantly better version.
    print("???: ");
    print(file);
    print(":");
    print_number(line);
    print(": ");
    print(func);
    print("Assertion `");
    print(expr);
    print("' failed.");
}
