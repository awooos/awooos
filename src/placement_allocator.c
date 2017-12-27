#include <dmm.h>
#include "placement_allocator.h"

unsigned int placement;

unsigned int dmm_pa_kernel_end;

void dmm_placement_allocator_init(unsigned int kernel_end)
{
    dmm_pa_kernel_end = kernel_end;
    placement = dmm_pa_kernel_end;
}

/* malloc(size, flags)
 * Simple placement based allocator. This allocates off the end of the kernel.
 * Potential bugs: This has no bound, and does not check with the final heap allocator
 */
void *kmalloc_int(unsigned int size, unsigned int flags)
{
    // Otherwise, increment to next placement address.
    placement += size;

    // Align on a page if needed.
    if ((flags & MALLOC_ALIGN) && ((placement) & 0x0fff)) {
        placement &= 0xfffff000;
        placement += 0x1000;
    }

    return (void*)placement;
}
