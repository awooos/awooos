#include <stdio.h>
#include <tinker.h>

void add_dmm_tests(void);

char *shitty_print(const char *str) {
    size_t len = strlen(str);

    for (size_t idx = 0; idx < len; idx++) {
        putchar(str[idx]);
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
