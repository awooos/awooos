#include <tinker.h>
#include <stdint.h>
#include <stddef.h>
#include "shellsplit_test.h"
#include "charsplit_test.h"

void add_ali_str_tests(void)
{
    tinker_add_test(ali_str_shellsplit);
    tinker_add_test(ali_str_charsplit);
}
