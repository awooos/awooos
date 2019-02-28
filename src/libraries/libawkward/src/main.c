#include <stdint.h>

/*
// 64-bit division for non-64-bit systems.
uint64_t __udivdi3(uint64_t a, uint64_t b)
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
*/

// 64-bit multiplication with overflow detection.
uint64_t __mulodi4(uint64_t a, uint64_t b, int *overflow)
{
    // `(a * b) > c` if and only if `a > (c / b)`.
    // UINT64_MAX is c.
    // Thus, `a > (UINT64_MAX / b)` implies `(a * b) > c`
    if (b > 0 && a > (UINT64_MAX / b)) {
        *overflow = 1;
    } else {
        *overflow = 0;
    }
    return a * b;
}
