#include <ktest.h>
#include <stddef.h>
#include <dmm.h>
#include "main.h"

size_t test_dmm_malloc()
{
    TEST_HAS_ASSERTIONS();

    void *region = dmm_malloc(10);
    TEST_ASSERT(region != NULL);

    DMM_MallocHeader *header = ((DMM_MallocHeader*)region) - 1;

    TEST_ASSERT(header->size == 10);
    TEST_ASSERT(header->used == 1);
    TEST_ASSERT(header->data == region);

    TEST_ASSERTIONS_RETURN();
}

size_t test_dmm_free_sets_header()
{
    TEST_HAS_ASSERTIONS();

    void *region = dmm_malloc(10);
    TEST_ASSERT(region != NULL);

    DMM_MallocHeader *header = ((DMM_MallocHeader*)region) - 1;

    TEST_ASSERT(header->used == 1);

    dmm_free(region);

    TEST_ASSERT(header->used == 0);

    TEST_ASSERTIONS_RETURN();
}

void add_dmm_tests()
{
    TEST(dmm_malloc);
    TEST(dmm_free_sets_header);
}
