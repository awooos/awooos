#include <ktest.h>
#include <awoo/tests.h>
#include <ali/signedness.h>

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
    TEST(ali_signedness_assertions);
}
