#include <stdio.h>
#include <tinker.h>

void add_dmm_tests(void);

char *shitty_print(const char *str) {
    for (char *s = (char*)str; *s; s++) {
        putchar(*s);
    }
    return (char*)str;
}

int main(void)
{
    add_dmm_tests();

    if (!tinker_run_tests(&shitty_print)) {
        return 1;
    }

    return 0;
}
