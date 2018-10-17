#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

static int digit(char c) {
    if ('0' <= c && c <= '9')
        return (c - '0');

    else if ('a' <= c && c <= 'z')
        return ((c - 'a') + 10);

    else if ('A' <= c && c <= 'Z')
        return ((c - 'A') + 10);

    else return INT_MAX;
}

static bool is_digit(char c, int base) {
    return digit(c) < base;
}

long long int strtoll(const char *nptr, char **endptr, int base)
{
    long long int ret = 0;
    bool neg = false;

    if(*nptr == '-') {
        neg = true;
        nptr++;
    }

    for(; is_digit(*nptr, base); nptr++)
        ret = base * ret + digit(*nptr);

    if(endptr != NULL)
        *endptr = (char*)nptr;

    return neg ? -ret : ret;
}

long int strtol(const char *nptr, char **endptr, int base)
{
    return (long int)strtoll(nptr, endptr, base);
}

int atoi(const char *nptr)
{
    return (int)strtol(nptr, NULL, 10);
}

long atol(const char *nptr)
{
    return (long)strtoll(nptr, NULL, 10);
}

long long atoll(const char *nptr)
{
    return strtoll(nptr, NULL, 10);
}

