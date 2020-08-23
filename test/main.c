#include "../include/flail.h"
#include <stddef.h>
#include <stdio.h>


void flail_stack_dump(void) {
    puts("<insert stack dump here>");
}

void flail_wait_forever(void) {
    // Do nothing.
}


int main(void) {
    flail_init("Flail test executable", &putchar);

    test_flail_intentional_panic();

    return 0;
}
