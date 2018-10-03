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
    uint64_t ret = 0;
    *overflow = 0;

    while (b-- > 0) {
        if (ret > (UINT64_MAX - a)) {
            *overflow = 1;
            break;
        }

        ret += a;
    }
    return ret;
}
