#include <tinker.h>
#include <stddef.h>
#include <dmm.h>
#include "main.h"
#include "main_test.h"

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

size_t test_dmm_allocate_the_universe()
{
    DMM_MallocHeader *header;

    // Allocate everything
    while (1) {
        void *region = dmm_malloc(ALLOCATE_THE_UNIVERSE_CHUNK_SIZE);
        if (region == NULL) {
            break;
        }

        header = ((DMM_MallocHeader*)region) - 1;
        header->flags = DMM_HEADER_FLAG_TEST;
    }

    // Check that all the allocations with the test flag set are of the size
    // we expect them to be
    header = dmm_global_instance;
    while (1) {
        if (header == NULL) {
            break;
        }

        if ((header->flags & DMM_HEADER_FLAG_TEST) == 1) {
            if (header->size != (ALLOCATE_THE_UNIVERSE_CHUNK_SIZE - sizeof(DMM_MallocHeader))) {
                TEST_RETURN(TEST_FAILURE, "An allocated test chunk was not of the expected size.");
            }
        }

        header = header->next;
    }

    // Free all the test allocations
    header = dmm_global_instance;
    while (1) {
        if (header == NULL) {
            break;
        }

        // Save the value of header->next in case the header disappears when we
        // free() the region (when DMM actually merges free regions)
        DMM_MallocHeader *next = header->next;
        if ((header->flags & DMM_HEADER_FLAG_TEST) == 1) {
            header->flags = 0;
            dmm_free(header->data);
        }

        header = next;
    }

    TEST_RETURN(TEST_SUCCESS, "Allocating the universe test passed.");
}
