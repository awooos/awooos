#include <ktest.h>
#include <stdint.h>
#include <awoo/tests.h>

#define MULTIBOOT_MAGIC 0x2BADB002

uint32_t hal_get_magic();

TestResult *test_hal_assertions()
{
    TEST_HAS_ASSERTIONS();

    TEST_ASSERT(hal_get_magic() == MULTIBOOT_MAGIC);

    TEST_ASSERTIONS_RETURN();
}

void add_hal_tests()
{
    TEST(hal_assertions);
}
