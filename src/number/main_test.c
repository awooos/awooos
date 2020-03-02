#include <tinker.h>
#include <stdint.h>
#include <string.h>
#include <ali/number.h>

void test_ali_n_to_str_assertions()
{
    tinker_assert(decimal_places_in_uint64(0, 10) == 1);
    tinker_assert(decimal_places_in_uint64(10, 10) == 2);
    tinker_assert(decimal_places_in_uint64(11, 10) == 2);
    tinker_assert(decimal_places_in_uint64(20, 10) == 2);
    tinker_assert(decimal_places_in_uint64(21, 10) == 2);

    tinker_assert(uint64_div(10, 2) == 5);
    tinker_assert(uint64_div(12, 4) == 3);

    // Make sure uint64_div(); rounds predictably.
    tinker_assert(uint64_div(100, 3) == 33);
    tinker_assert(uint64_div(53, 12) == 4);
    tinker_assert(uint64_div(9034, 703) == 12);

    tinker_assert(uint64_mod(10, 10) == 0);
    tinker_assert(uint64_mod(13, 10) == 3);
    tinker_assert(uint64_mod(53, 12) == 5);
    tinker_assert(uint64_mod(53, 13) == 1);
    tinker_assert(uint64_mod(3, 10) == 3);
    tinker_assert(uint64_mod(10, 3) == 1);

    tinker_assert(strcmp(n_to_str_radix(10, 16), "a") == 0);
    tinker_assert(strcmp(n_to_str_radix(30, 16), "1e") == 0);
    tinker_assert(strcmp(n_to_str_radix(430, 16), "1ae") == 0);
    tinker_assert(strcmp(n_to_str_radix(430, 26), "ge") == 0);

    tinker_assert(strcmp(n_to_str(0), "0") == 0);
    tinker_assert(strcmp(n_to_str(1), "1") == 0);
    tinker_assert(strcmp(n_to_str(2), "2") == 0);
    tinker_assert(strcmp(n_to_str(123), "123") == 0);
    tinker_assert(strcmp(n_to_str(9001), "9001") == 0);

    TINKER_ASSERTIONS_FINISH();
}

void test_ali_is_number()
{
    void *not_a_number;

    tinker_assert(is_number(1) == 1);
    tinker_assert(is_number(not_a_number) == 0);
    tinker_assert(is_number(test_ali_is_number) == 0);

    TINKER_ASSERTIONS_FINISH();
}

void test_ali_signedness_assertions()
{
    // Unsigned +1. Should return 1.
    tinker_assert(is_unsigned((unsigned char)1) == 1);
    tinker_assert(is_unsigned((unsigned short)1) == 1);
    tinker_assert(is_unsigned((unsigned int)1) == 1);
    tinker_assert(is_unsigned((unsigned long)1) == 1);
    tinker_assert(is_unsigned((unsigned long long)1) == 1);

    // Unsigned -1. Should return 1.
    tinker_assert(is_unsigned((unsigned char)-1) == 1);
    tinker_assert(is_unsigned((unsigned short)-1) == 1);
    tinker_assert(is_unsigned((unsigned int)-1) == 1);
    tinker_assert(is_unsigned((unsigned long)-1) == 1);
    tinker_assert(is_unsigned((unsigned long long)-1) == 1);

    // Signed +1. Should return 0.
    tinker_assert(is_unsigned((signed char)1) == 0);
    tinker_assert(is_unsigned((signed short)1) == 0);
    tinker_assert(is_unsigned((signed int)1) == 0);
    tinker_assert(is_unsigned((signed long)1) == 0);
    tinker_assert(is_unsigned((signed long long)1) == 0);

    // Signed -1. Should return 0.
    tinker_assert(is_unsigned((signed char)-1) == 0);
    tinker_assert(is_unsigned((signed short)-1) == 0);
    tinker_assert(is_unsigned((signed int)-1) == 0);
    tinker_assert(is_unsigned((signed long)-1) == 0);
    tinker_assert(is_unsigned((signed long long)-1) == 0);

    // Unsigned +255. Should return 1.
    tinker_assert(is_unsigned((unsigned char)255) == 1);
    tinker_assert(is_unsigned((unsigned short)255) == 1);
    tinker_assert(is_unsigned((unsigned int)255) == 1);
    tinker_assert(is_unsigned((unsigned long)255) == 1);
    tinker_assert(is_unsigned((unsigned long long)255) == 1);

    // Unsigned -255. Should return 1.
    tinker_assert(is_unsigned((unsigned char)-255) == 1);
    tinker_assert(is_unsigned((unsigned short)-255) == 1);
    tinker_assert(is_unsigned((unsigned int)-255) == 1);
    tinker_assert(is_unsigned((unsigned long)-255) == 1);
    tinker_assert(is_unsigned((unsigned long long)-255) == 1);

    // Signed +255. Should return 0.
    tinker_assert(is_unsigned((signed char)255) == 0);
    tinker_assert(is_unsigned((signed short)255) == 0);
    tinker_assert(is_unsigned((signed int)255) == 0);
    tinker_assert(is_unsigned((signed long)255) == 0);
    tinker_assert(is_unsigned((signed long long)255) == 0);

    // Signed -255. Should return 0.
    tinker_assert(is_unsigned((signed char)-255) == 0);
    tinker_assert(is_unsigned((signed short)-255) == 0);
    tinker_assert(is_unsigned((signed int)-255) == 0);
    tinker_assert(is_unsigned((signed long)-255) == 0);
    tinker_assert(is_unsigned((signed long long)-255) == 0);

    TINKER_ASSERTIONS_FINISH();
}

void add_ali_number_tests()
{
    tinker_add_test(ali_n_to_str_assertions);
    tinker_add_test(ali_is_number);
    tinker_add_test(ali_signedness_assertions);
}
