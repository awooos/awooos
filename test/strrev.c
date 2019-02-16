#include <stdlib.h>
#include <string.h>

// copypasta'd from ali for simplicity.
char *strrev(char *str)
{
    size_t length = strlen(str);
    size_t half_length = length / 2;

    for (size_t idx = 0; idx < half_length; idx++) {
        char tmp = str[idx];
        str[idx] = str[length - idx - 1];
        str[length - idx - 1] = tmp;
    }

    return str;
}

