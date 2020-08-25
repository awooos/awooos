#include <flail.h>
#include <flail/platform.h>
#include <stddef.h>
#include <stdio.h>


void flail_stack_dump(void) {
    // The stack is assumed to be an array of size_t values, in pairs,
    // where each pair has the address of the previous frame followed by a
    // value.
    //
    // The first item is 0x0, which is less-than-or-equal to the designated
    // `stack_end` value (which in this case is also 0x0).
    size_t stack[11] = {0};

    // NULL terminator.
    stack[0] = 0x0;

    // Item #1.
    stack[1] = (size_t)(stack + 0); // previous frame
    stack[2] = 0x9999999999999999; // Biggest integer size_t can fit.

    // Item #2.
    stack[3] = (size_t)(stack + 1); // previous frame
    stack[4] = 0xdeadbeef; // Arbitrary, easily-identified value.

    // Item #3.
    stack[5] = (size_t)(stack + 3); // previous frame
    stack[6] = 0xbadf00d; // Arbitrary, easily-identified value.

    // Item #4.
    stack[7] = (size_t)(stack + 5); // previous frame
    stack[8] = 0x2; // Arbitrary value.

    // Item #5.
    stack[9] = (size_t)(stack + 7); // next frame
    stack[10] = 0x1; // smallest valid value.

    flail_stack_dump_with_stack(stack + 9, stack);
}


int main(void) {
    flail_init("Flail test executable", &putchar);

    test_flail_intentional_panic();

    return 0;
}
