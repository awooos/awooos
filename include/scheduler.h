#ifndef AWOO_SCHEDULER_H
#define AWOO_SCHEDULER_H

#include <stdbool.h>

typedef struct process_s {
    size_t id;
    uint8_t used;
} Process;

#endif
