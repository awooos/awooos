#include <ktest.h>
#include <stdint.h>
#include <awoostr.h>
#include <awoo/tests.h>
#include <stdlib.h>

TestResult *test_malloc_initializes_buffer()
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
    TEST(malloc_initializes_buffer);
}
