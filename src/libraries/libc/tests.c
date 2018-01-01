#include <ktest.h>
#include <stdint.h>
#include <awoostr.h>
#include <awoo/tests.h>
#include <stdlib.h>
#include "malloc.h"

size_t test_malloc_sets_header()
{
    TEST_HAS_ASSERTIONS();

    size_t length = 100;
    void *buffer = malloc(length);
    MallocHeader *malloc_header = (MallocHeader*)(buffer) - 1;

    TEST_ASSERT(malloc_header->size == length);
    TEST_ASSERT(malloc_header->used == true);
    TEST_ASSERT(malloc_header->data == buffer);

    TEST_ASSERTIONS_RETURN();
}

size_t test_free_adjusts_header()
{
    TEST_HAS_ASSERTIONS();

    size_t length = 100;
    void *buffer = malloc(length);
    MallocHeader *malloc_header = (MallocHeader*)(buffer) - 1;

    TEST_ASSERT(malloc_header->used == true);

    free(buffer);

    TEST_ASSERT(malloc_header->used == false);

    TEST_ASSERTIONS_RETURN();
}

size_t test_malloc_initializes_buffer()
{
    size_t length = 100;
    uint8_t *buffer = malloc(length);

    for (size_t i = 0; i < length; i++) {
        if (buffer[i] != 0) {
            TEST_RETURN(TEST_FAILURE, "malloc() did not initialize entire buffer to null bytes!");
        }
    }

    TEST_RETURN(TEST_SUCCESS, "malloc() initializes entire buffer to null bytes.");
}

void add_libc_tests()
{
    TEST(malloc_sets_header);
    TEST(free_adjusts_header);
    TEST(malloc_initializes_buffer);
}
