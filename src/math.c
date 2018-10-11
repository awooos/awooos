#include "math.h"

int32_t abs(int32_t n) {
    if (n < 0) {
        return n * -1;
    } else {
        return n;
    }
}

double fabs(double n) {
    if (n < 0) {
        return n * -1.0;
    } else {
        return n;
    }
}

double sqrt(double n)
{
    double guess = 10.0, newn;
    int i;

    /* This algorithm works as follows:
     * 1. Make a guess and divide the number to be squared by it.
     * 2. Average the result of number 1 and the guess. This becomes the next guess.
     * 3. Repeat.
     * 4. There is no step 4.
     */

    for (i = 0; i < 100; i++) {
        newn = n/guess;
        guess = (newn + n)/2.0;
        n = newn;
    }

    return n;
}

