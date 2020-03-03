#include <string.h>
#include <tinker.h>

char *tinker_uint_to_str(unsigned long n);

void test_tinker_uint_to_str(void)
{
    tinker_assert(strcmp(tinker_uint_to_str(0), "0") == 0);
    tinker_assert(strcmp(tinker_uint_to_str(1), "1") == 0);
    tinker_assert(strcmp(tinker_uint_to_str(2), "2") == 0);
    tinker_assert(strcmp(tinker_uint_to_str(123), "123") == 0);
    tinker_assert(strcmp(tinker_uint_to_str(9001), "9001") == 0);
}

void add_tinker_main_tests(void)
{
    tinker_add_test(tinker_uint_to_str);
}
