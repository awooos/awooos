#include <tinker.h>
#include <math.h>
#include <stddef.h>

void test_ali_abs_assertions(void) {
    tinker_assert(abs(0) == 0);
    tinker_assert(abs(1) == 1);
    tinker_assert(abs(-1) == 1);

/* TODO: Figure out how to avoid relying on certain levels of precision. */
/*
    tinker_assert(fabs(0.0) == 0.0);
    tinker_assert(fabs(0.1) == 0.1);
    tinker_assert(fabs(-0.1) == 0.1);
    tinker_assert(fabs(1.0) == 1.0);
    tinker_assert(fabs(-1.0) == 1.0);
    tinker_assert(fabs(1.1) == 1.1);
    tinker_assert(fabs(-1.1) == 1.1);
*/
}


/* TODO: Figure out a way to avoid relying on certain levels of precision. */
/*
void test_ali_sqrt_assertions(void)
{
    tinker_assert(sqrt(2.0) == 1.414213562373095);
    tinker_assert(sqrt(3.0) == 1.7320508075688772);
    tinker_assert(sqrt(4.0) == 2.0);
    tinker_assert(sqrt(5.0) == 2.23606797749979);
    tinker_assert(sqrt(6.0) == 2.449489742783178);
    tinker_assert(sqrt(7.0) == 2.6457513110645907);
    tinker_assert(sqrt(8.0) == 2.828427124746190);
    tinker_assert(sqrt(9.0) == 3.0);

    tinker_assert(sqrt(10.0) == 3.162277660168379);
    tinker_assert(sqrt(20.0) == 4.47213595499958);
    tinker_assert(sqrt(30.0) == 5.477225575051661);
    tinker_assert(sqrt(40.0) == 6.3245553203367586);
    tinker_assert(sqrt(50.0) == 7.0710678118654755);
    tinker_assert(sqrt(60.0) == 7.745966692414834);
    tinker_assert(sqrt(70.0) == 8.366600265340756);
    tinker_assert(sqrt(80.0) == 8.94427190999916);
    tinker_assert(sqrt(90.0) == 9.486832980505138);
}
*/

void add_ali_math_tests(void)
{
    tinker_add_test(ali_abs_assertions);
    //tinker_add_test(ali_sqrt_assertions);
}
