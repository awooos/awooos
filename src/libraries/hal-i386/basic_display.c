/// Mmmmmm, that sweet memory-mapped VGA goodness.

#include <kernel/hal_basic_display.h>
#include <stdint.h>

const uint16_t *VIDEO_RAM = (const uint16_t*)0xB8000;

static uint16_t VIDEO_WIDTH  = 80; /* characters. */
static uint16_t VIDEO_HEIGHT = 25; /* rows. */

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
    static uint8_t row = 0;
    static uint8_t col = 0;

    uint8_t text_index;
    uint8_t color_index;

    if (video == 0) {
        video = (char*)VIDEO_RAM;
    }

    for (; 0 != *string; string++)
    {
        if (*string == '\r') {
            col = 0;
        } else if (*string == '\n') {
//            col = 0;
            row += 1;
        } else {
/*            if (col >= VIDEO_WIDTH) {
                col = 0;
                row += 1;
            }
            if (row >= VIDEO_HEIGHT) {
                row = 0; // TODO: deal with scrolling.
            }
*/
            text_index = ((row * VIDEO_WIDTH) + col) * 2;
            color_index = text_index + 1;
            video[text_index] = *string;
            video[color_index] = BACKGROUND_COLOR;
            col++;
        }
    }
}
