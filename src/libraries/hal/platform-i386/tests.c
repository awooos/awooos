#include <tinker.h>
#include <stdint.h>

#define MULTIBOOT_MAGIC 0x2BADB002

uint32_t hal_get_magic(void);

void test_hal_assertions()
{
    tinker_assert(hal_get_magic() == MULTIBOOT_MAGIC);

    TINKER_ASSERTIONS_FINISH();
}

void add_hal_tests()
{
    tinker_add_test(hal_assertions);
}
