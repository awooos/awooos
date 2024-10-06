#include <tinker.h>
#include <stddef.h>

void test_dmm_malloc(void);
void test_dmm_free_sets_header(void);
void test_dmm_allocate_the_universe(void);

void test_dmm_instance_add_region(void);
void test_dmm_instance_malloc(void);
void test_dmm_instance_free_sets_header(void);

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
