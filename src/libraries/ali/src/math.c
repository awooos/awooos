#include <math.h>

int abs(int n) {
    if (n < 0) {
        return -n;
    } else {
        return n;
    }
}

double fabs(double n) {
    if (n < 0) {
        return -n;
    } else {
        return n;
    }
}

double sqrt(double n)
{
    /* This is using the "Babylonian method", which works as follows:
     * 1. Make a guess.
     * 2. Divide `n` by the guess, then average it with the guess. This is your next guess.
     * 3. Repeat step 2 until you reach the desired precision.
     */

    double guess = n / 2;
    for (int i = 0; i < 100; i++) {
        guess = (guess + (n / guess)) / 2;
    }
    return guess;
}
