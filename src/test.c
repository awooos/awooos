#include <tinker.h>
#include <stdint.h>
#include <stddef.h>
#include "main_test.h"
#include "instance_test.h"

void add_dmm_tests()
{
    // Global instance tests
    TEST(dmm_malloc);
    TEST(dmm_free_sets_header);
    TEST(dmm_allocate_the_universe);

    // Local instance tests
    TEST(dmm_instance_add_region);
    TEST(dmm_instance_malloc);
    TEST(dmm_instance_free_sets_header);
}
