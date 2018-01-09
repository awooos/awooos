#include <ktest.h>
#include <stddef.h>
#include <dmm.h>
#include "main.h"

size_t test_dmm_add_region()
{
    TEST_HAS_ASSERTIONS();

    // XXX: this assumes that the first 1040 bytes of memory are unused.
    // This is (generally) the case on i386, but may not be on other
    // architectures. Ideally, the region that this uses should be set
    // per-platform, but for now, this is fine.
    void *address = 0x0000000F;
    size_t length = 1024;

    dmm_add_memory_region(address, length);

    DMM_MallocHeader *header = (DMM_MallocHeader*)address;

    TEST_ASSERT(header->size == length - sizeof(DMM_MallocHeader));
    TEST_ASSERT(header->used == 0);
    TEST_ASSERT(header->data == (void*)(header + 1));

    TEST_ASSERTIONS_RETURN();
}

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
    //TEST(dmm_add_region);
    TEST(dmm_malloc);
    TEST(dmm_free_sets_header);
}
