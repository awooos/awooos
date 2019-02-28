#include <tinker.h>
#include <stddef.h>
#include <stdint.h>
#include "main.h"

size_t test_awkward_assertions()
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

void add_awkward_tests()
{
    tinker_add_test(awkward_assertions);
}
