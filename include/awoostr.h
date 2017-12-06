#ifndef AWOOSTR_H
#define AWOOSTR_H

#include <stddef.h>
#include <stdint.h>

char *_uint64_to_str_radix_with_negative_check(uint64_t n, size_t radix, bool is_negative);

size_t _decimal_places_in_uint(uint64_t n, size_t radix);

uint64_t uint64_div(uint64_t a, uint64_t b);
uint64_t uint64_mod(uint64_t a, uint64_t b);

char *uint64_to_str_radix(uint64_t n, size_t radix);
char *uint64_to_str(uint64_t n);
char *int64_to_str_radix(int64_t n, size_t radix);
char *int64_to_str(int64_t n);

#define str(x) _Generic((x),    uint8_t:  uint64_to_str, \
                                uint16_t: uint64_to_str, \
                                uint32_t: uint64_to_str, \
                                uint64_t: uint64_to_str, \
                                int8_t:   int64_to_str,  \
                                int16_t:  int64_to_str,  \
                                int32_t:  int64_to_str,  \
                                int64_t:  int64_to_str)(x)

#define n_to_str_radix(n, radix) _Generic((n),  uint8_t:  uint64_to_str_radix, \
                                                uint16_t: uint64_to_str_radix, \
                                                uint32_t: uint64_to_str_radix, \
                                                uint64_t: uint64_to_str_radix, \
                                                int8_t:   int64_to_str_radix,  \
                                                int16_t:  int64_to_str_radix,  \
                                                int32_t:  int64_to_str_radix,  \
                                                int64_t:  int64_to_str_radix)(n, radix)

#endif
