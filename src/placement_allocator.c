#include <dmm.h>
#include <stddef.h>
#include "placement_allocator.h"

size_t placement;

size_t dmm_pa_kernel_end;

void dmm_placement_allocator_init(size_t kernel_end)
{
    dmm_pa_kernel_end = kernel_end;
    placement = dmm_pa_kernel_end;
}

/* malloc(size, flags)
 * Simple placement based allocator. This allocates off the end of the kernel.
 * Potential bugs: This has no bound, and does not check with the final heap allocator
 */
void *kmalloc_int(size_t size, size_t flags)
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
