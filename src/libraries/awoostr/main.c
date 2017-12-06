#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <badmalloc.h>

//#define is_digit(c) ((c) >= '0' && (c) <= '9')

#define decimal_places_in(n, radix) _decimal_places_in_uint((uint64_t)n, radix)

// YOLO
uint64_t uint64_div(uint64_t a, uint64_t b)
{
    uint64_t tmp = 0;

    if (a < b) {
        return 0;
    }

    while (a > b) {
        a -= b;
        tmp += 1;
    }

    if (a > 0) {
        tmp += 1;
    }

    return tmp;
}

// YOLO × 2
uint64_t uint64_mod(uint64_t a, uint64_t b)
{
    while (a >= b) {
        a -= b;
    }
    return a;
}

size_t _decimal_places_in_uint(uint64_t n, size_t radix)
{
    size_t decimal_places = 0;
    uint64_t tmp = n;

    while (tmp >= 1) {
        decimal_places += 1;
        tmp = uint64_div(tmp, radix);
    }

    return decimal_places;
}

// Converts a +uint64_t+ to a string, using the base specified in +radix+,
// prepending a negative sign if told to do so.
//
// ASSUMPTION: radix is small enough that all values can fit in a char.
char *_uint64_to_str_radix_with_negative_check(uint64_t n, size_t radix, bool is_negative)
{
    char *result;
    uint64_t tmp = n;
    uint8_t start = 0;

    size_t decimal_places = decimal_places_in(n, radix);
    if (is_negative) {
        decimal_places += 1;
        start = 1;
    }

    result = (char*)badmalloc(decimal_places + 1);
    memset(result, 0, decimal_places + 1);

    for (size_t idx = decimal_places - 1; idx <= start; idx -= 1) {
        result[idx] = '0' + (char)uint64_mod(tmp, radix);
        tmp = uint64_div(tmp, radix);
    }

    if (is_negative) {
        result[0] = '-';
    }

    return result;
}

// Converts an unsigned integer to a string, in the base specified by +radix+.
char *uint64_to_str_radix(uint64_t n, size_t radix)
{
    return _uint64_to_str_radix_with_negative_check(n, radix, false);
}

// Converts an unsigned integer to a string, in base 10.
char *uint64_to_str(uint64_t n)
{
    return uint64_to_str_radix(n, 10);
}

// Converts an integer to a string, in the base specified by +radix+.
char *int64_to_str_radix(int64_t n, size_t radix)
{
    bool is_negative = false;
    if (n < 0) {
        is_negative = true;
        n = -n;
    }

    return _uint64_to_str_radix_with_negative_check((uint64_t)n, radix, is_negative);
}

// Converts an integer to a string, in base 10.
char *int64_to_str(int64_t n)
{
    return int64_to_str_radix(n, 10);
}


