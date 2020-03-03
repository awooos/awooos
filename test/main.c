#include <stdio.h>
#include <tinker.h>

int main(void)
{
    if (!tinker_run_tests(&putchar)) {
        return 1;
    }

    return 0;
}
