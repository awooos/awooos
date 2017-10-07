/// Mmmmmm, that sweet memory-mapped VGA goodness.

#include <kernel/hal_basic_display.h>
#include <stdint.h>

const uint16_t *VIDEO_RAM = (const uint16_t*)0xB8000;

static uint16_t VIDEO_WIDTH  = 80; /* characters. */
//static uint16_t VIDEO_HEIGHT = 25; /* rows. */

// http://wiki.osdev.org/Printing_To_Screen
static char BACKGROUND_COLOR = 0x07; /* Light gray on black. */

/*
 * Very basic function for printing text.
 *
 * TODO: Scrolling?
 */
void hal_basic_display_print(const char *string)
{
    static char *video = 0;

    if (video == 0) {
        video = (char*)VIDEO_RAM;
    }

    while(0 != *string)
    {
        if (*string == '\r') {
            *video -= (*video % VIDEO_WIDTH);
        }
        if (*string == '\n') {
            *video += VIDEO_WIDTH;
        }

        *video++ = *string++;
        *video++ = BACKGROUND_COLOR;
    }
}
