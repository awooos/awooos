#include <ktest.h>
#include <stdint.h>
#include <awoo/tests.h>
#include <stdlib.h>
#include "malloc.h"

size_t test_malloc_sets_header()
{
    TEST_HAS_ASSERTIONS();

    size_t length = 100;
    void *buffer = malloc(length);
    MallocHeader *malloc_header = _malloc_header_for(buffer);

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
    MallocHeader *malloc_header = _malloc_header_for(buffer);

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

size_t test_calloc_allocates_correct_size()
{
    TEST_HAS_ASSERTIONS();

    size_t nmemb = 10;
    MallocHeader *malloc_header = NULL;

    // Test calloc() with an array of uint8_ts.
    uint8_t *buffer = calloc(nmemb, sizeof(uint8_t));
    malloc_header = _malloc_header_for(buffer);
    TEST_ASSERT(malloc_header->size == (sizeof(uint8_t) * nmemb));

    // Test calloc() with an array of size_ts.
    size_t *buffer2 = calloc(nmemb, sizeof(size_t));
    malloc_header = _malloc_header_for(buffer2);
    TEST_ASSERT(malloc_header->size == (sizeof(size_t) * nmemb));

    // Test calloc() with an array of MallocHeaders.
    MallocHeader *buffer3 = calloc(nmemb, sizeof(MallocHeader));
    malloc_header = _malloc_header_for(buffer3);
    TEST_ASSERT(malloc_header->size == (sizeof(MallocHeader) * nmemb));

    TEST_ASSERTIONS_RETURN();
}

size_t test_realloc_frees_old_and_allocates_new()
{
    TEST_HAS_ASSERTIONS();

    // Tests the allocation system by doing an initial calloc(),
    // realloc()ing different sizes twice, then realloc()ing with the same size
    // once.

    size_t nmemb = 10;

    uint8_t *buffer = calloc(nmemb, sizeof(uint8_t));
    uint8_t *old_buffer;
    MallocHeader *malloc_header = NULL;
    MallocHeader *old_malloc_header = NULL;

    malloc_header = _malloc_header_for(buffer);
    TEST_ASSERT(malloc_header->size == (sizeof(uint8_t) * nmemb));
    TEST_ASSERT(malloc_header->used == true);

    old_buffer = buffer;
    buffer = realloc(buffer, nmemb + 1);
    old_malloc_header = malloc_header;
    malloc_header = _malloc_header_for(buffer);
    TEST_ASSERT(malloc_header->size == (sizeof(uint8_t) * (nmemb + 1)));
    TEST_ASSERT(malloc_header->used == true);
    TEST_ASSERT(old_malloc_header->used == false);

    old_buffer = buffer;
    buffer = realloc(buffer, nmemb + 2);
    old_malloc_header = malloc_header;
    malloc_header = _malloc_header_for(buffer);
    TEST_ASSERT(malloc_header->size == (sizeof(uint8_t) * (nmemb + 2)));
    TEST_ASSERT(malloc_header->used == true);
    TEST_ASSERT(old_malloc_header->used == false);

    old_buffer = buffer;
    old_malloc_header = malloc_header;
    size_t old_malloc_header_size = old_malloc_header->size;
    buffer = realloc(buffer, nmemb + 2); // Same size as last realloc().
    malloc_header = _malloc_header_for(buffer);
    TEST_ASSERT(malloc_header->size > 0);
    TEST_ASSERT(malloc_header->size == (sizeof(uint8_t) * (nmemb + 2)));
    TEST_ASSERT(malloc_header->size == old_malloc_header_size);
    TEST_ASSERT(malloc_header->used == true);
    TEST_ASSERT(old_malloc_header->used == false);

    old_buffer = buffer;
    buffer = realloc(buffer, nmemb); // Shrink back to the original size.
    old_malloc_header = malloc_header;
    malloc_header = _malloc_header_for(buffer);
    TEST_ASSERT(malloc_header->size == (sizeof(uint8_t) * nmemb));
    TEST_ASSERT(malloc_header->used == true);
    TEST_ASSERT(old_malloc_header->used == false);

    TEST_ASSERTIONS_RETURN();
}

void add_libc_tests()
{
    TEST(malloc_sets_header);
    TEST(free_adjusts_header);
    TEST(malloc_initializes_buffer);
    TEST(calloc_allocates_correct_size);
    TEST(realloc_frees_old_and_allocates_new);
}
