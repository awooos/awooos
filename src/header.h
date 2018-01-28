#ifndef DMM_HEADER_H
#define DMM_HEADER_H

#include <stddef.h>
#include <stdint.h>

#define DMM_HEADER_MAGIC 0x99A3E7D6
#define DMM_UNASSIGNED_REGION NULL

typedef struct dmm_malloc_header_s {
    uint32_t magic;
    size_t size;
    size_t used; // A bit space-inefficient, but means we only require one type.
    void *data;
    struct dmm_malloc_header_s *next;
} DMM_MallocHeader;

#endif
