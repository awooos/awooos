#include <dmm.h>
#include <kernel.h> // Provided by the system using this library.
#include <stddef.h>
#include <string.h> // Provided by the system using this library.
#include "frames.h"

static size_t *frames;
static size_t end_memory;

#define DMM_ASSERT(code) if (!(code)) { panic(#code); }

/* set_frame(addr)
 * Allocates a frame in the frames array. It is assumed to be large enough to
 * hold whatever address you are allocating!
 */
void dmm_set_frame(size_t addr)
{
    size_t frame = addr/0x1000;
    frames[frame/32] |= (size_t)0x1<<frame%32;
}

/* clear_frame(addr)
 * Clears a frame in the frames array. It is assumed to be large enough to
 * hold whatever address you are clearing!
 */
void dmm_clear_frame(size_t addr)
{
    size_t frame = addr/0x1000;
    frames[frame/32] &= ~((size_t)0x1<<frame%32);
}

/* test_frame(addr)
 * Returns 0 if a frame is free or anything else if a frame is not free. It
 * will not cause data loss if frame is not large enough, but will produce
 * erratic results.
 */
size_t dmm_test_frame(size_t addr)
{
    size_t frame = addr/0x1000;
    return frames[frame/32] & ((size_t)0x1<<frame%32);
}

size_t dmm_first_frame()
{
    size_t i;

    for (i = 0; i < end_memory; i+=0x1000) {
        if (!dmm_test_frame(i)) {
            return i;
        }
    }

    panic((char*)"No free frames.\n");
}

/* alloc_frame(page, is_kernel, is_writable)
 * Obtains a physical frame and allocates it to the page table given.
 */
int dmm_alloc_frame(PageTableEntry *page, int is_kernel, int is_writable)
{
    size_t addr;

    // Was the frame already allocated?
    if (page->address != 0)
        return -1;

    addr = dmm_first_frame();
    dmm_set_frame(addr);

    DMM_ASSERT((addr>>12) < 1048576); // (addr>>12) < 2^20

    page->present = 1;
    page->user = is_kernel ? 0 : 1;
    page->readwrite = is_writable ? 1 : 0;
    page->address = addr>>12;
    return 0;
}

/* free_frame(page)
 * Clears the allocation on the physical frame
 */
void dmm_free_frame(PageTableEntry *page)
{
    dmm_clear_frame((size_t)page->address<<12);
    page->address = 0x0;
}

/* setup_frames()
*/
void dmm_frames_init(size_t _end_memory)
{
    end_memory = _end_memory;

    frames = (size_t*) kmalloc_int(end_memory / 0x1000, 0);
    memset(frames, 0, end_memory / 0x1000 / 8);
}
