#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

//#define is_digit(c) ((c) >= '0' && (c) <= '9')

#define decimal_places_in(n, radix) _decimal_places_in_uint((uint64_t)n, radix)

// YOLO
uint64_t uint64_div(uint64_t a, uint64_t b)
{
    uint64_t tmp = 0;

    if (a < b) {
        return 0;
    }

    while (a >= b) {
        a -= b;
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

    if (decimal_places == 0) {
        decimal_places = 1;
    }

    return decimal_places;
}

extern void kprint(const char*);
char uint8_to_char(uint8_t value)
{
    if (value < 10) { // 0-9
        return '0' + (char)value;
    } else if (value >= 10 && value < 36) { // A-Z
        return 'a' + (char)value - 10;
    } else {
        // Not a representable character.
        // Good luck have fun.
        return '?';
    }
}

// Converts a +uint64_t+ to a string, using the base specified in +radix+.
//
// ASSUMPTION: radix is small enough that all values can fit in a char.
char *uint64_to_str_radix(uint64_t n, size_t radix)
{
    char *result;
    uint8_t value;
    uint64_t tmp = n;

    size_t decimal_places = decimal_places_in(n, radix);

    result = (char*)malloc(decimal_places);
    memset(result, 0, decimal_places);

    for (size_t idx = 0; idx < decimal_places; idx++) {
        value = (uint8_t)uint64_mod(tmp, radix);
        result[idx] = uint8_to_char(value);
        tmp = uint64_div(tmp, radix);
    }

    result[decimal_places] = 0;

    return strrev(result);
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

    return uint64_to_str_radix((uint64_t)n, radix);
}

// Converts an integer to a string, in base 10.
char *int64_to_str(int64_t n)
{
    return int64_to_str_radix(n, 10);
}


