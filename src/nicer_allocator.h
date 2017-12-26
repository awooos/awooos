#ifndef DMM_NICER_ALLOCATOR
#define DMM_NICER_ALLOCATOR

#include <dmm.h>
#include "frames.h"

typedef long Align;

union header {
	struct {
		union header *ptr;
		unsigned size;
	} s;
	Align x;
};

typedef union header Header;

#define NALLOC 4096 - sizeof(Header)

#endif
