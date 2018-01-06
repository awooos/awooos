#include "src/uint_to_str.h"
#include <stdio.h>

int main()
{
    char buffer[UINT64_CHARS_WITH_NULL];
    puts(flail_uint_to_str(buffer, 1234, 16));

    return 0;
}
