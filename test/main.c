#include <stdio.h>
#include <tinker.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void add_dmm_tests(void);

char *int64_to_str(int64_t n)
{
    char *str = malloc(10);
    memset(str, 0, 10);
    snprintf(str, 10, "%li", n);
    return str;
}

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
