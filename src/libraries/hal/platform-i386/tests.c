#include <tinker.h>
#include <stdint.h>

#define MULTIBOOT_MAGIC 0x2BADB002

uint32_t hal_get_magic(void);

int test_hal_assertions()
{
    TEST_HAS_ASSERTIONS();

    TEST_ASSERT(hal_get_magic() == MULTIBOOT_MAGIC);

    TEST_ASSERTIONS_RETURN();
}

void add_hal_tests()
{
    tinker_add_test(hal_assertions);
}
