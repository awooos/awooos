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
     * 1. Make a guess and divide the number to be squared by it.
     * 2. Average the result of number 1 and the guess. This becomes the next guess.
     * 3. Repeat step 2 until you reach the desired precision.
     */

    double guess = 10.0;

    for (int i = 0; i < 100; i++) {
        double newn = n/guess;
        guess = (newn + n)/2.0;
        n = newn;
    }

    return n;
}

