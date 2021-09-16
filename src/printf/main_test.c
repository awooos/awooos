#include <tinker.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sprintn_test.h"

void test_ali_printf_assertions(void)
{
    char str[20];
    int ret;

    // Set str to the letter "x" repeated 19 times.
    memset(str, (int)'x', 19);
    str[19] = 0;
    // Test snprintf with a string and no format options.
    ret = snprintf(str, 20, "bork bork\n");
    tinker_assert(ret > 0);
    tinker_assert(strncmp((const char*)str, "bork bork\n", 20) == 0);

    // Set str to the letter "x" repeated 19 times.
    memset(str, (int)'x', 19);
    str[19] = 0;
    // Test snprintf with %s, %c, %%, %d, %u, %i.
    // This test uses %s twice because that was a common failure point
    // in a prior attempt at implementing printf().
    ret = snprintf(str, 20, "%s %c%% %d %u %i %s", "foo", 'a', 2, 3, -4, "bar");
    tinker_assert(ret == 17);
    tinker_assert(strncmp((const char*)str, "foo a% 2 3 -4 bar", 20) == 0);

    // Set str to the letter "x" repeated 19 times.
    memset(str, (int)'x', 19);
    str[19] = 0;
    // Test snprintf using escaped test (\r, \n, etc).
    ret = snprintf(str, 20, "a\nb\rc\r\nd");
    tinker_assert(ret == 8);
    tinker_assert(strncmp((const char*)str, "a\nb\rc\r\nd", 20) == 0);

    // Set str to the letter "x" repeated 19 times.
    memset(str, (int)'x', 19);
    str[19] = 0;
    // Test snprintf using %o, %x, %X.
    ret = snprintf(str, 20, "%o %x %X", 30, 30, 30);
    tinker_assert(strncmp((const char*)str, "36 1e 1E", 20) == 0);

    // Set str to the letter "x" repeated 19 times.
    memset(str, (int)'x', 19);
    str[19] = 0;
    // Test snprintf using %p.
    void *ptr = (void*)0x1234ef7;
    ret = snprintf(str, 20, "0x%p", ptr);
    tinker_assert(strncmp((const char*)str, "0x1234ef7", 20) == 0);

    // Set str to the letter "x" repeated 19 times.
    memset(str, (int)'x', 19);
    str[19] = 0;
    // Test snprintf using %e, %E (scientific notation).
    tinker_skip("no %e or %E support");

    // Set str to the letter "x" repeated 19 times.
    memset(str, (int)'x', 19);
    str[19] = 0;
    // Test snprintf using %f, %F (floating point).
    tinker_skip("no %f or %F support");

    // Set str to the letter "x" repeated 19 times.
    memset(str, (int)'x', 19);
    str[19] = 0;
    // Test snprintf using %g, %G (floating point).
    tinker_skip("no %g or %G support");

    // Set str to the letter "x" repeated 19 times.
    memset(str, (int)'x', 19);
    str[19] = 0;
    // Test snprintf using %a, %A (floating point).
    tinker_skip("no %a or %A support");
}

void add_ali_printf_tests(void)
{
    tinker_add_test(ali_printf_assertions);
    tinker_add_test(ali_sprintn_assertions);
}
