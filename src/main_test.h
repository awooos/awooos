#ifndef DMM_MAIN_TEST_H
#define DMM_MAIN_TEST_H

#include <stddef.h>
#include <dmm.h>
#include "main.h"

// FIXME: dmm can't handle >634K chunk sizes for some reason.
#define ALLOCATE_THE_UNIVERSE_CHUNK_SIZE (634 * 1024) // 634K
//#define ALLOCATE_THE_UNIVERSE_CHUNK_SIZE (1024 * 1024) // 1M

size_t test_dmm_malloc(void);
size_t test_dmm_free_sets_header(void);
size_t test_dmm_allocate_the_universe(void);

#endif
