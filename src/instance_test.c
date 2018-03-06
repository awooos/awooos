#include <tinker.h>
#include <stddef.h>
#include <dmm.h>
#include <dmm_instance.h>
#include "header.h"
#include "instance.h"
#include "instance_test.h"

DMM_MallocHeader *test_instance = DMM_UNASSIGNED_REGION;

size_t test_dmm_instance_add_region()
{
    TEST_HAS_ASSERTIONS();

    size_t length = 128;

    void *region = dmm_malloc(length);
    TEST_ASSERT(region != NULL); // sanity check

    void *result = dmm_instance_add_memory_region(test_instance, region, length);
    TEST_ASSERT(result != DMM_UNASSIGNED_REGION);
    TEST_ASSERT(result != NULL);
    test_instance = result;

    // Actually check the header
    DMM_MallocHeader *header = (DMM_MallocHeader *)region;
    TEST_ASSERT(header->size == length - sizeof(DMM_MallocHeader));
    TEST_ASSERT(header->used == 0);
    TEST_ASSERT(header->data == (void *)(header + 1));

    TEST_ASSERTIONS_RETURN();
}

size_t test_dmm_instance_malloc()
{
    TEST_HAS_ASSERTIONS();

    void *region = dmm_instance_malloc(test_instance, 10);
    TEST_ASSERT(region != NULL);

    DMM_MallocHeader *header = ((DMM_MallocHeader*)region) - 1;

    TEST_ASSERT(header->size == 10);
    TEST_ASSERT(header->used == 1);
    TEST_ASSERT(header->data == region);

    TEST_ASSERTIONS_RETURN();
}

size_t test_dmm_instance_free_sets_header()
{
    TEST_HAS_ASSERTIONS();

    void *region = dmm_instance_malloc(test_instance, 10);
    TEST_ASSERT(region != NULL);

    DMM_MallocHeader *header = ((DMM_MallocHeader*)region) - 1;

    TEST_ASSERT(header->used == 1);

    dmm_instance_free(test_instance, region);

    TEST_ASSERT(header->used == 0);

    TEST_ASSERTIONS_RETURN();
}
