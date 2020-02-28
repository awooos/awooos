#include <tinker.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ali/str.h>

#include "shellsplit_test.h"

size_t test_ali_str_shellsplit()
{
    TEST_HAS_ASSERTIONS();

    const char *test_str = "test \"test test\" 'test test' test\\ test";
    ShellSplitResult *test_output = shellsplit((char*)test_str);
    TEST_ASSERT(test_output->num_pieces == 4);
    TEST_ASSERT(strcmp(test_output->pieces[0], "test") == 0);
    TEST_ASSERT(strcmp(test_output->pieces[1], "test test") == 0);
    TEST_ASSERT(strcmp(test_output->pieces[2], "test test") == 0);
    TEST_ASSERT(strcmp(test_output->pieces[3], "test test") == 0);

    TEST_ASSERTIONS_RETURN();
}

