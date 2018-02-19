#include <ktest.h>
#include <stdint.h>
#include <stddef.h>
#include "shellsplit_test.h"
#include "charsplit_test.h"

void add_ali_str_tests()
{
    TEST(ali_str_shellsplit);
    TEST(ali_str_charsplit);
}
