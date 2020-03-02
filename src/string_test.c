#include <tinker.h>
#include <stddef.h>
#include <string.h>

int test_ali_string_assertions(void)
{
    TEST_HAS_ASSERTIONS();

    char *str1 = "HAL shutdown";
    char *str2 = "HAL shutdown test failure";

    TEST_ASSERT(strncmp(str1, str2, 25) != 0);

    TEST_ASSERT(strcmp(str1, str2) != 0);
    TEST_ASSERT(strcmp(str1, str2) == -32);

    TEST_ASSERTIONS_RETURN();
}

void add_ali_string_tests(void)
{
    tinker_add_test(ali_string_assertions);
}
