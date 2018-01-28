#ifndef ALI__ALI_STR_H
#define ALI__ALI_STR_H

#include <stddef.h>
#include <stdint.h>
#include <ali/numbers.h>

size_t _decimal_places_in_uint(uint64_t n, size_t radix);

uint64_t uint64_div(uint64_t a, uint64_t b);
uint64_t uint64_mod(uint64_t a, uint64_t b);

char *uint64_to_str_radix(uint64_t n, size_t radix);
char *uint64_to_str(uint64_t n);
char *int64_to_str_radix(int64_t n, size_t radix);
char *int64_to_str(int64_t n);

#define uint_to_str_radix(n, radix) uint64_to_str_radix((uint64)(n), radix)
#define  int_to_str_radix(n, radix)  int64_to_str_radix((uint64)(n), radix)

#define uint_to_str(n) uint_to_str_radix((n), 10)
#define  int_to_str(n)  int_to_str_radix((n), 10)

#define n_to_str_radix(n, radix) (is_signed(n) ? int_to_str(n) : uint_to_str(n))
#define n_to_str(n) n_to_str_radix(n, 10)

#endif
