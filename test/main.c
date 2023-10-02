#include <dmm.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <tinker.h>

void test_dmm_malloc(void);
void test_dmm_free_sets_header(void);
void test_dmm_allocate_the_universe(void);

void test_dmm_instance_add_region(void);
void test_dmm_instance_malloc(void);
void test_dmm_instance_free_sets_header(void);

noreturn void _panic(const char *message, const char *function,
        const char *filename, size_t line)
{
    // loosely copy Rust's panic message format.
    fprintf(stderr, "function '%s' panicked at '%s', %s:%zu\n", function, message, filename, line);
    exit(1);
}

typedef struct mmap_entry_s {
    char *data;
    size_t size;
} mmap_entry;

void new_mmap_entry(mmap_entry *entry, size_t size) {
    entry->data = malloc(size);
    memset(entry->data, 0, size);
    entry->size = size;
    dmm_add_memory_region(entry->data, entry->size);
}

static mmap_entry mmaps[10];
void init_mmap(void) {
    for (size_t idx = 0; idx < 10; idx++) {
        new_mmap_entry(&mmaps[idx], 1024 * 1024 * (idx + 1));
    }
}

void deinit_mmap(void) {
    for (size_t idx = 0; idx < 10; idx++) {
        free(mmaps[idx].data);
    }
}

int main(void)
{
    // Global instance tests
    tinker_add_test(dmm_malloc);
    tinker_add_test(dmm_free_sets_header);
    tinker_add_test(dmm_allocate_the_universe);

    // Local instance tests
    tinker_add_test(dmm_instance_add_region);
    tinker_add_test(dmm_instance_malloc);
    tinker_add_test(dmm_instance_free_sets_header);

    dmm_init(&_panic);

    init_mmap();
    if (!tinker_run_tests(&putchar)) {
        deinit_mmap();
        return 1;
    }

    deinit_mmap();
    return 0;
}
