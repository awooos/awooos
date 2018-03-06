#include <tinker.h>
#include <stdint.h>
#include <stdlib.h>
#include <ali/str.h>

#include "charsplit_test.h"

size_t test_ali_str_charsplit()
{
    TEST_HAS_ASSERTIONS();

    const char *test_str = "test!test two!test three";
    char **test_output = charsplit((char *)test_str, '!');
    TEST_ASSERT(strcmp(test_output[0], "test") == 0);
    TEST_ASSERT(strcmp(test_output[1], "test two") == 0);
    TEST_ASSERT(strcmp(test_output[2], "test three") == 0);

    TEST_ASSERTIONS_RETURN();
}

