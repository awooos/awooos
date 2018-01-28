#ifndef DMM_INSTANCE_H
#define DMM_INSTANCE_H

#include <stddef.h>
#include <stdint.h>
#include "header.h"

DMM_MallocHeader *dmm_instance_get_first_free_chunk(void *instance, size_t size);

#endif
