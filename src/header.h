#ifndef DMM_HEADER_H
#define DMM_HEADER_H

#include <stddef.h>

#define DMM_HEADER_MAGIC 0x99A3E7D6
#define DMM_UNASSIGNED_REGION NULL
#define DMM_HEADER_FLAG_TEST ((size_t)1 << 31)

// ASSUMPTION: Function name is less than 64 bytes long.
// ASSUMPTION: The last 64 bytes of the file name is Good Enough(TM).
typedef struct dmm_call_location_s {
    char function[64];
    char filename[64];
    size_t line;
} DMM_CallLocation;

typedef struct dmm_malloc_header_s {
    size_t magic;
    size_t size;
    size_t used; // A bit space-inefficient, but means we only require one type.
    size_t flags; // Currently only used for tests
    void *data;
    struct dmm_malloc_header_s *next;
    DMM_CallLocation call_location;
} DMM_MallocHeader;

#endif
