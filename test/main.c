#include <stdio.h>
#include <tinker.h>

void add_tinker_uint_to_str_tests(void);
void add_tinker_assert_tests(void);

int main(void)
{
    add_tinker_uint_to_str_tests();
    add_tinker_assert_tests();

    if (!tinker_run_tests(&putchar)) {
        return 1;
    }

    return 0;
}
