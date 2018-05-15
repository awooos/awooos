// NOTE: This display driver does NOT implement scrolling, currently.

#include <ali/modifiers.h>
#include "basic_display.h"
#include "ports.h"
#include <stdint.h>
#include <string.h>

const uint16_t *VIDEO_RAM = (const uint16_t*)0xB8000;

#define VIDEO_WIDTH  80 /* characters. */
#define VIDEO_HEIGHT 25 /* rows. */

#define DISPLAY_BUFFER_SIZE (sizeof(char) * VIDEO_HEIGHT * VIDEO_WIDTH)

// http://www.jamesmolloy.co.uk/tutorial_html/3.-The%20Screen.html
static uint16_t VGA_CTRL_REGISTER = 0x3D4;
static uint16_t VGA_DATA_REGISTER = 0x3D5;

// http://wiki.osdev.org/Printing_To_Screen
static char BACKGROUND_COLOR = 0x07; /* Light gray on black. */

static uint8_t row = 0;
static uint8_t col = 0;

// Move the cursor to a different position, and update row/column accordingly.
void hal_basic_display_move_cursor(uint8_t row_, uint8_t col_)
{
    uint16_t position = (row_ * VIDEO_WIDTH) + col_;
    row = row_;
    col = col_;

    hal_outb(VGA_CTRL_REGISTER, 14);                // Tell it we're setting high cursor byte.
    hal_outb(VGA_DATA_REGISTER, (position >> 8));   // Actually set it.
    hal_outb(VGA_CTRL_REGISTER, 15);                // Tell it we're setting the low cursor byte.
    hal_outb(VGA_DATA_REGISTER, (uint8_t)position); // Actually set it.
}

void hal_basic_display_scroll()
{
    for (uint16_t i = 0; i < (VIDEO_HEIGHT - 1); i++) {
        memcpy((void*)(VIDEO_RAM + (i * VIDEO_WIDTH)),
               (void*)(VIDEO_RAM + ((i + 1) * VIDEO_WIDTH)),
               VIDEO_WIDTH * 2);
    }
    memset((void*)(VIDEO_RAM + ((VIDEO_HEIGHT - 1) * VIDEO_WIDTH)),
            0, VIDEO_WIDTH * 2);
}

// Print a string to the display.
void hal_basic_display_print(const char *string)
{
    static char *video = 0;

    uint16_t text_index;
    uint16_t color_index;

    if (video == 0) {
        video = (char*)VIDEO_RAM;
    }

    for (; 0 != *string; string++) {
        if (*string == '\r') {
            col = 0;
        } else if (*string == '\n') {
            col = 0;
            row += 1;
        } else {
            if (col >= VIDEO_WIDTH) {
                col = 0;
                row += 1;
            }
            if (row >= VIDEO_HEIGHT) {
                hal_basic_display_scroll();
                row = VIDEO_HEIGHT - 1;
            }

            text_index = ((row * VIDEO_WIDTH) + col) * 2;
            color_index = text_index + 1;
            video[text_index] = *string;
            video[color_index] = BACKGROUND_COLOR;

            col++;
        }
    }

    hal_basic_display_move_cursor(row, col);
}

void hal_basic_display_clear()
{
    static char spaces[DISPLAY_BUFFER_SIZE + 1] = {' ',};
    spaces[DISPLAY_BUFFER_SIZE] = 0;

    hal_basic_display_print(spaces);
    hal_basic_display_move_cursor(0, 0);
}

void hal_basic_display_init(UNUSED void *data)
{
    hal_basic_display_clear();
}
