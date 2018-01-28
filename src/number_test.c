#include <ktest.h>
#include <awoo/tests.h>
#include <ali/number.h>

size_t test_ali_is_number()
{
    __attribute__((unused)) void *not_a_number;

    TEST_HAS_ASSERTIONS();

    TEST_ASSERT(is_number(1) == 1);
    TEST_ASSERT(is_number(not_a_number) == 0);
    TEST_ASSERT(is_number(test_ali_is_number) == 0);

    TEST_ASSERTIONS_RETURN();
}

size_t test_ali_signedness_assertions()
{
    TEST_HAS_ASSERTIONS();

    // Unsigned +1.
    TEST_ASSERT(is_unsigned((unsigned char)1) == 1);
    TEST_ASSERT(is_unsigned((unsigned short)1) == 1);
    TEST_ASSERT(is_unsigned((unsigned int)1) == 1);
    TEST_ASSERT(is_unsigned((unsigned long)1) == 1);
    TEST_ASSERT(is_unsigned((unsigned long long)1) == 1);

    // Unsigned -1.
    TEST_ASSERT(is_unsigned((unsigned char)-1) == 1);
    TEST_ASSERT(is_unsigned((unsigned short)-1) == 1);
    TEST_ASSERT(is_unsigned((unsigned int)-1) == 1);
    TEST_ASSERT(is_unsigned((unsigned long)-1) == 1);
    TEST_ASSERT(is_unsigned((unsigned long long)-1) == 1);

    // Signed +1.
    TEST_ASSERT(is_unsigned((signed char)1) == 1);
    TEST_ASSERT(is_unsigned((signed short)1) == 1);
    TEST_ASSERT(is_unsigned((signed int)1) == 1);
    TEST_ASSERT(is_unsigned((signed long)1) == 1);
    TEST_ASSERT(is_unsigned((signed long long)1) == 1);

    // Signed -1.
    TEST_ASSERT(is_unsigned((signed char)-1) == 1);
    TEST_ASSERT(is_unsigned((signed short)-1) == 1);
    TEST_ASSERT(is_unsigned((signed int)-1) == 1);
    TEST_ASSERT(is_unsigned((signed long)-1) == 1);
    TEST_ASSERT(is_unsigned((signed long long)-1) == 1);

    // Unsigned +255.
    TEST_ASSERT(is_unsigned((unsigned char)255) == 1);
    TEST_ASSERT(is_unsigned((unsigned short)255) == 1);
    TEST_ASSERT(is_unsigned((unsigned int)255) == 1);
    TEST_ASSERT(is_unsigned((unsigned long)255) == 1);
    TEST_ASSERT(is_unsigned((unsigned long long)255) == 1);

    // Unsigned -255.
    TEST_ASSERT(is_unsigned((unsigned char)-255) == 1);
    TEST_ASSERT(is_unsigned((unsigned short)-255) == 1);
    TEST_ASSERT(is_unsigned((unsigned int)-255) == 1);
    TEST_ASSERT(is_unsigned((unsigned long)-255) == 1);
    TEST_ASSERT(is_unsigned((unsigned long long)-255) == 1);

    // Signed +255.
    TEST_ASSERT(is_unsigned((signed char)255) == 1);
    TEST_ASSERT(is_unsigned((signed short)255) == 1);
    TEST_ASSERT(is_unsigned((signed int)255) == 1);
    TEST_ASSERT(is_unsigned((signed long)255) == 1);
    TEST_ASSERT(is_unsigned((signed long long)255) == 1);

    // Signed -255.
    TEST_ASSERT(is_unsigned((signed char)-255) == 1);
    TEST_ASSERT(is_unsigned((signed short)-255) == 1);
    TEST_ASSERT(is_unsigned((signed int)-255) == 1);
    TEST_ASSERT(is_unsigned((signed long)-255) == 1);
    TEST_ASSERT(is_unsigned((signed long long)-255) == 1);

    TEST_ASSERTIONS_RETURN();
}

void add_ali_signedness_tests()
{
    TEST(ali_is_number);
    TEST(ali_signedness_assertions);
}
