#include <tinker.h>
#include <stddef.h>
#include <string.h>

void test_ali_string_assertions(void)
{
    char *str1 = "HAL shutdown";
    char *str2 = "HAL shutdown test failure";

    tinker_assert(strncmp(str1, str2, 25) != 0);

    tinker_assert(strcmp(str1, str2) != 0);
    tinker_assert(strcmp(str1, str2) == -32);

    TINKER_ASSERTIONS_FINISH();
}

void add_ali_string_tests(void)
{
    tinker_add_test(ali_string_assertions);
}
