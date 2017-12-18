#include <ktest.h>
#include <stdint.h>
#include <awoostr.h>
#include <awoo/tests.h>

TestResult *test_awoostr_assertions()
{
    TEST_HAS_ASSERTIONS();

    TEST_ASSERT(_decimal_places_in_uint(0, 10) == 1);
    TEST_ASSERT(_decimal_places_in_uint(10, 10) == 2);
    TEST_ASSERT(_decimal_places_in_uint(11, 10) == 2);
    TEST_ASSERT(_decimal_places_in_uint(20, 10) == 2);
    TEST_ASSERT(_decimal_places_in_uint(21, 10) == 2);

    TEST_ASSERT(uint64_div(10, 2) == 5);
    TEST_ASSERT(uint64_div(12, 4) == 3);

    // Make sure uint64_div(); rounds predictably.
    TEST_ASSERT(uint64_div(100, 3) == 33);
    TEST_ASSERT(uint64_div(53, 12) == 4);
    TEST_ASSERT(uint64_div(9034, 703) == 12);

    TEST_ASSERT(uint64_mod(10, 10) == 0);
    TEST_ASSERT(uint64_mod(13, 10) == 3);
    TEST_ASSERT(uint64_mod(53, 12) == 5);
    TEST_ASSERT(uint64_mod(53, 13) == 1);
    TEST_ASSERT(uint64_mod(3, 10) == 3);
    TEST_ASSERT(uint64_mod(10, 3) == 1);

    TEST_ASSERT(strcmp(n_to_str_radix(10, 16), "a") == 0);
    TEST_ASSERT(strcmp(n_to_str_radix(30, 16), "1e") == 0);
    TEST_ASSERT(strcmp(n_to_str_radix(430, 16), "1ae") == 0);
    TEST_ASSERT(strcmp(n_to_str_radix(430, 26), "ge") == 0);

    TEST_ASSERT(strcmp(str(0), "0") == 0);
    TEST_ASSERT(strcmp(str(1), "1") == 0);
    TEST_ASSERT(strcmp(str(2), "2") == 0);
    TEST_ASSERT(strcmp(str(123), "123") == 0);
    TEST_ASSERT(strcmp(str(9001), "9001") == 0);

    TEST_ASSERTIONS_RETURN();
}

void add_awoostr_tests()
{
    TEST(awoostr_assertions);
}
