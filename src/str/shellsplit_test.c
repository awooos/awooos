#include <tinker.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ali/str.h>

#include "shellsplit_test.h"

void test_ali_str_shellsplit()
{
    const char *test_str = "test \"test test\" 'test test' test\\ test";
    ShellSplitResult *test_output = shellsplit((char*)test_str);
    tinker_assert(test_output->num_pieces == 4);
    tinker_assert(strcmp(test_output->pieces[0], "test") == 0);
    tinker_assert(strcmp(test_output->pieces[1], "test test") == 0);
    tinker_assert(strcmp(test_output->pieces[2], "test test") == 0);
    tinker_assert(strcmp(test_output->pieces[3], "test test") == 0);

    tinker_pass();
}
