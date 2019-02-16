#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *int64_to_str(int64_t n)
{
    char *str = malloc(10);
    memset(str, 0, 10);
    snprintf(str, 10, "%li", n);
    return str;
}
