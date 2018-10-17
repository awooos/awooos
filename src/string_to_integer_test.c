#include <tinker.h>
#include <stdint.h>
#include <stdlib.h>
#include <ali/number.h>

size_t test_ali_str_to_int_assertions(void)
{
    TEST_HAS_ASSERTIONS();

    TEST_ASSERT(atoi("10") == 10);
    TEST_ASSERT(atoi("1234567890") == 1234567890);
    TEST_ASSERT(atoi("000000001234567890") == 1234567890);

    TEST_ASSERT(atoi("-0") == 0);
    TEST_ASSERT(atoi("-10") == -10);
    TEST_ASSERT(atoi("-1234567890") == -1234567890);
    TEST_ASSERT(atoi("-000000001234567890") == -1234567890);

    TEST_ASSERT(strtol("abcd", NULL, 16) == 0xabcd);
    TEST_ASSERT(strtol("ABCD", NULL, 16) == 0xABCD);
    TEST_ASSERT(strtoll("12a3bc89f", NULL, 16) == 0x12a3bc89f);

    TEST_ASSERT(strtol("-abcd", NULL, 16) == -0xabcd);
    TEST_ASSERT(strtol("-ABCD", NULL, 16) == -0xABCD);
    TEST_ASSERT(strtoll("-12a3bc89f", NULL, 16) == -0x12a3bc89f);

    const char *str = "-12a9 NaN 4321";
    char *end10;
    char *end16;
    TEST_ASSERT(strtoll("-12a9 NaN 4321", &end16, 16) == -0x12a9);
    TEST_ASSERT(strtoll("-12a9 NaN 4321", &end10, 10) == -12);
    TEST_ASSERT(end16 == str + 5);
    TEST_ASSERT(end10 == str + 3);

    TEST_ASSERTIONS_RETURN();
}

void add_ali_str_to_int_tests(void)
{
    tinker_add_test(ali_str_to_int_assertions);
}
