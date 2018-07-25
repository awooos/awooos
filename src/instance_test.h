#ifndef DMM_INSTANCE_TEST_H
#define DMM_INSTANCE_TEST_H

#include <stddef.h>
#include <dmm.h>
#include <dmm_instance.h>
#include "main.h"
#include "instance.h"

size_t test_dmm_instance_add_region(void);
size_t test_dmm_instance_malloc(void);
size_t test_dmm_instance_free_sets_header(void);

#endif
