#include <ktest.h>
#include <stdint.h>
#include <stdlib.h>
#include <ali/str.h>

#include "shellsplit_test.h"

size_t test_ali_str_shellsplit()
{
    TEST_HAS_ASSERTIONS();

    const char *test_str = "test \"test test\" 'test test' test\\ test";
    char **test_output = shellsplit((char *)test_str);
    TEST_ASSERT(strcmp(test_output[0], "test") == 0);
    TEST_ASSERT(strcmp(test_output[1], "test test") == 0);
    TEST_ASSERT(strcmp(test_output[2], "test test") == 0);
    TEST_ASSERT(strcmp(test_output[3], "test test") == 0);

    TEST_ASSERTIONS_RETURN();
}

