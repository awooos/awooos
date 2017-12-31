#include <ktest.h>
#include <stdint.h>
#include <awoostr.h>
#include <awoo/tests.h>
#include <badmalloc.h>

TestResult *test_badmalloc_initializes_buffer()
{
    size_t length = 100;
    uint8_t *buffer = badmalloc(length);

    for (size_t i = 0; i < length; i++) {
        if (buffer[i] != 0) {
            TEST_RETURN(TEST_FAILURE, "badmalloc() did not initialize entire buffer to null bytes!");
        }
    }

    TEST_RETURN(TEST_SUCCESS, "badmalloc() initializes entire buffer to null bytes.");
}

void add_badmalloc_tests()
{
    TEST(badmalloc_initializes_buffer);
}
