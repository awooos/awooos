#include <tinker.h>
#include <ctype.h>

void test_ali_ctype_assertions(void)
{
    tinker_assert(toupper('!') == '!');
    tinker_assert(toupper('"') == '"');
    tinker_assert(toupper(';') == ';');

    tinker_assert(toupper('a') == 'A');
    tinker_assert(toupper('b') == 'B');
    tinker_assert(toupper('y') == 'Y');
    tinker_assert(toupper('z') == 'Z');
    tinker_assert(toupper('!') == '!');


    tinker_assert(tolower('!') == '!');
    tinker_assert(tolower('"') == '"');
    tinker_assert(tolower(';') == ';');

    tinker_assert(tolower('A') == 'a');
    tinker_assert(tolower('B') == 'b');
    tinker_assert(tolower('Y') == 'y');
    tinker_assert(tolower('Z') == 'z');
    tinker_assert(tolower('!') == '!');
}

void add_ali_ctype_tests(void)
{
    tinker_add_test(ali_ctype_assertions);
}
