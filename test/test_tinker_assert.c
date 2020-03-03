#include <tinker.h>

char *tinker_uint_to_str(unsigned long n);

void test_tinker_assert(void)
{

}

void add_tinker_assert_tests(void)
{
    tinker_add_test(tinker_assert);
}
