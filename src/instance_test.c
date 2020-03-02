#include <tinker.h>
#include <stddef.h>
#include <dmm.h>
#include <dmm_instance.h>
#include "header.h"
#include "instance.h"
#include "instance_test.h"

static DMM_MallocHeader *test_instance = DMM_UNASSIGNED_REGION;

void test_dmm_instance_add_region()
{
    size_t length = 128;

    void *region = dmm_malloc(length);
    tinker_assert(region != NULL); // sanity check

    void *result = dmm_instance_add_memory_region(test_instance, region, length);
    tinker_assert(result != DMM_UNASSIGNED_REGION);
    tinker_assert(result != NULL);
    test_instance = result;

    // Actually check the header
    DMM_MallocHeader *header = (DMM_MallocHeader *)region;
    tinker_assert(header->size == length - sizeof(DMM_MallocHeader));
    tinker_assert(header->used == 0);
    tinker_assert(header->data == (void *)(header + 1));

    tinker_pass();
}

void test_dmm_instance_malloc()
{
    void *region = dmm_instance_malloc(test_instance, 10);
    tinker_assert(region != NULL);

    DMM_MallocHeader *header = ((DMM_MallocHeader*)region) - 1;

    tinker_assert(header->size == 10);
    tinker_assert(header->used == 1);
    tinker_assert(header->data == region);

    tinker_pass();
}

void test_dmm_instance_free_sets_header()
{
    void *region = dmm_instance_malloc(test_instance, 10);
    tinker_assert(region != NULL);

    DMM_MallocHeader *header = ((DMM_MallocHeader*)region) - 1;

    tinker_assert(header->used == 1);

    dmm_instance_free(test_instance, region);

    tinker_assert(header->used == 0);

    tinker_pass();
}
