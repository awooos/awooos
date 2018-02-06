#ifndef DMM_MAIN_TEST_H
#define DMM_MAIN_TEST_H

#include <stddef.h>
#include <dmm.h>
#include "main.h"

#define ALLOCATE_THE_UNIVERSE_CHUNK_SIZE (1024 * 1024) // 1M

size_t test_dmm_malloc();
size_t test_dmm_free_sets_header();
size_t test_dmm_allocate_the_universe();

#endif
