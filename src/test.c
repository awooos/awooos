#include <tinker.h>
#include <stdint.h>
#include <stddef.h>
#include "main_test.h"
#include "instance_test.h"

void add_dmm_tests()
{
    // Global instance tests
    tinker_add_test(dmm_malloc);
    tinker_add_test(dmm_free_sets_header);
    tinker_add_test(dmm_allocate_the_universe);

    // Local instance tests
    tinker_add_test(dmm_instance_add_region);
    tinker_add_test(dmm_instance_malloc);
    tinker_add_test(dmm_instance_free_sets_header);
}
