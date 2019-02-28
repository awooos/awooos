#include <stdint.h>

// 64-bit division with modulo.
uint64_t __udivmoddi4(uint64_t n, uint64_t d, uint64_t *rem)
{
    // TODO: What is the _proper_ way to handle this?
    if (d == 0) { return 1 / d; }

    uint64_t q = 0;
    uint64_t tmp = n;

    for (uint64_t idx = 0; idx < 64; idx++) {
        if (d > tmp) {
            continue;
        }

        tmp -= d;
        q++;
        d = d << 1;
    }

    *rem = tmp;

    return q;
}

// 64-bit division for non-64-bit systems.
uint64_t __udivdi3(uint64_t a, uint64_t b)
{
    return __udivmoddi4(a, b, 0);
}

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
