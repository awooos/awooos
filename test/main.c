#include "../include/flail.h"
#include "../src/main.h"
#include <stddef.h>
#include <stdio.h>


void flail_stack_dump(void) {
    size_t stack[6] = {
        0x1,                // Smallest valid/non-NULL value.
        0x2,                // Arbitrary.
        0xbadf00d,          // Arbitrary.
        0xdeadbeef,         // Arbitrary.
        0x9999999999999999, // Biggest integer size_t can fit.
        0x0,                // Terminating NULL.
    };
    flail_stack_dump_hex(stack, stack + 5);
}

void flail_wait_forever(void) {
    // Do nothing.
}


int main(void) {
    flail_init("Flail test executable", &putchar);

    test_flail_intentional_panic();

    return 0;
}
