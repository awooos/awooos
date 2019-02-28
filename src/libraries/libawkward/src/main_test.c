#include <tinker.h>
#include <stddef.h>
#include <stdint.h>
#include "main.h"

size_t test_awkward_multiplication_assertions()
{
    TEST_HAS_ASSERTIONS();

    int overflow = 0;
    uint64_t ret;

    ret = __mulodi4(UINT64_MAX, 2, &overflow);
    TEST_ASSERT(overflow == 1);

    ret = __mulodi4(2, UINT64_MAX, &overflow);
    TEST_ASSERT(overflow == 1);

    ret = __mulodi4((UINT64_MAX - 1) / 2, 2, &overflow);
    TEST_ASSERT(overflow == 0);
    TEST_ASSERT(ret == (UINT64_MAX - 1));

    ret = __mulodi4(4, 13, &overflow);
    TEST_ASSERT(overflow == 0);
    TEST_ASSERT(ret == 52);

    TEST_ASSERTIONS_RETURN();
}

size_t test_awkward_division_assertions()
{
    TEST_HAS_ASSERTIONS();

    int remainder = 0;
    uint64_t ret;

    ret = __mulodi4(13, 2, &remainder);
    TEST_ASSERT(ret == 6);
    TEST_ASSERT(remainder == 1);

    ret = __mulodi4(1234567890123456789, 5, &remainder);
    TEST_ASSERT(ret == 246913578024691357);
    TEST_ASSERT(remainder == 4);

    TEST_ASSERTIONS_RETURN();
}

void add_awkward_tests()
{
    tinker_add_test(awkward_multiplication_assertions);
    tinker_add_test(awkward_division_assertions);
}
