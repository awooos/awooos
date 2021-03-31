#include <tinker.h>
#include <stddef.h>
#include <string.h>

void test_ali_string_assertions(void)
{
    char *str1 = "HAL shutdown";
    char *str2 = "HAL shutdown test failure";

    tinker_assert(strncmp(str1, str2, 25) != 0);

    tinker_assert(strcmp(str1, str2) != 0);
    tinker_assert(strcmp(str1, str2) == -32);

    tinker_assert(strlen("hello world") == 11);
    tinker_assert(strlen("beep boop") == 9);
    tinker_assert(strlen("") == 0);

    tinker_assert((char*)memchr(str1, ' ', 10) == str1 + 3);
    tinker_assert((unsigned long)((char*)memchr(str1, '\0', 13) - str1) == strlen(str1));
}

void add_ali_string_tests(void)
{
    tinker_add_test(ali_string_assertions);
}
