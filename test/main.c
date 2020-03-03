#include <stdio.h>
#include <tinker.h>
#include "test_main.h"

int main(void)
{
    add_tinker_main_tests();

    if (!tinker_run_tests(&putchar)) {
        return 1;
    }

    return 0;
}
