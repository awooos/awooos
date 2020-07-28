#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

static int digit(char c)
{
    if ('0' <= c && c <= '9') {
        return (c - '0');
    } else if ('a' <= c && c <= 'z') {
        return ((c - 'a') + 10);
    } else if ('A' <= c && c <= 'Z') {
        return ((c - 'A') + 10);
    } else {
        return -1;
    }
}

static bool is_digit(char c, int base)
{
    return digit(c) < base;
}

long long int strtoll(const char *nptr, char **endptr, int base)
{
    long long int ret = 0;
    bool neg = false;

    if (base == 0) {
        // TODO: Bullshit auto-detection that is apparently expected.
    }

    if (base < 2 || base > 36) {
        // TODO: errno = EINVAL;
        return -1;
    }

    if(*nptr == '-') {
        neg = true;
        nptr++;
    }

    for(; is_digit(*nptr, base); nptr++) {
        int d = digit(*nptr);
        if (d == -1) {
            // TODO: errno = ERANGE;
            if (endptr != NULL) {
                *endptr = (char*)nptr;
            }
            break;
        }

        ret = base * ret + d;
    }

    if(endptr != NULL) {
        *endptr = (char*)nptr;
    }

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
