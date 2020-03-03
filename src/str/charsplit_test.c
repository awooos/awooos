#include <tinker.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ali/str.h>

#include "charsplit_test.h"

void test_ali_str_charsplit()
{
    const char *test_str = "test!test two!test three";
    char **test_output = charsplit((char *)test_str, '!');
    tinker_assert(strcmp(test_output[0], "test") == 0);
    tinker_assert(strcmp(test_output[1], "test two") == 0);
    tinker_assert(strcmp(test_output[2], "test three") == 0);
}
