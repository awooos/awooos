#include <tinker.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vprintf.h"
#include "sprintn.h"

void test_ali_sprintn_assertions(void) {
    VprintFlags flags = {0};
    char str[10] = {0,};
    int ret;

    ret = ali_sprintnu(
        str, 10 /* size */, 1 /* min_length */, 123456 /* number */,
        10 /* base */, &flags, 0 /* uppercase */, 1 /* precision */
    );
    tinker_assert(ret == 6);
    tinker_assert(strncmp((const char*)str, "123456", 10) == 0);


    ret = ali_sprintni(
        str, 10 /* size */, 1 /* min_length */, -123456 /* number */,
        10 /* base */, &flags, 0 /* uppercase */, 1 /* precision */
    );
    tinker_assert(ret == 7);
    tinker_assert(strncmp((const char*)str, "-123456", 10) == 0);
}
