#ifndef FAKE_ALI_NUMBER_H
#define FAKE_ALI_NUMBER_H

#include <stdint.h>

char *int64_to_str(int64_t n);

#define n_to_str(n) int64_to_str((int64_t)(n))

#endif
