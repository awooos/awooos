#include <tinker.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void test_ali_string_assertions(void)
{
    char *str1 = "HAL shutdown";
    char *str2 = "HAL shutdown test failure";

    tinker_assert(strncmp(str1, str2, 25) != 0);

    tinker_assert(strcmp(str1, str2) != 0);
    tinker_assert(strcmp(str1, str2) == -32);

/*
    char *str3 = strdup(str1);
    tinker_assert(strncmp(str1, str3, 13) == 0);
    tinker_assert(strncmp(str1, "HAL shutdown", 13) == 0);

    str3[1] = 'x';
    tinker_assert(strncmp(str1, "HAL shutdown", 13) == 0);
    // If the HxL assertion passes, str3 is a duplicate of str1.
    tinker_assert(strncmp(str3, "HxL shutdown", 13) == 0);
    //free(str3); // FIXME: Why does free()ing this break things?
*/
    tinker_assert(strlen("hello world") == 11);
    tinker_assert(strlen("beep boop") == 9);
    tinker_assert(strlen("") == 0);

    tinker_assert((char*)memchr(str1, ' ', 10) == str1 + 3);
    tinker_assert((char*)memchr(str1, 'L', 10) == str1 + 2);
    tinker_assert((char*)memchr(str1, 'd', 10) == str1 + 8);

    tinker_assert(strnlen("hello world", 15) == 11);
    tinker_assert(strnlen("hello world", 11) == 11);
    tinker_assert(strnlen("hello world", 5) == 5);
}

void add_ali_string_tests(void)
{
    tinker_add_test(ali_string_assertions);
}
