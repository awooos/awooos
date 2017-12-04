/// Mmmmmm, that sweet memory-mapped VGA goodness.

#include <kernel/hal_basic_display.h>
#include "ports.h"
#include <stdint.h>

const uint16_t *VIDEO_RAM = (const uint16_t*)0xB8000;

static uint16_t VIDEO_WIDTH  = 80; /* characters. */
static uint16_t VIDEO_HEIGHT = 25; /* rows. */

// http://www.jamesmolloy.co.uk/tutorial_html/3.-The%20Screen.html
static uint16_t VGA_CTRL_REGISTER = 0x3D4;
static uint16_t VGA_DATA_REGISTER = 0x3D5;

// http://wiki.osdev.org/Printing_To_Screen
static char BACKGROUND_COLOR = 0x07; /* Light gray on black. */

static uint8_t row = 0;
static uint8_t col = 0;

void hal_basic_display_move_cursor(uint16_t row, uint16_t col)
{
    uint16_t position = (row * VIDEO_WIDTH) + col;

    hal_outb(VGA_CTRL_REGISTER, 14);                // Tell it we're setting high cursor byte.
    hal_outb(VGA_DATA_REGISTER, (position >> 8));   // Actually set it.
    hal_outb(VGA_CTRL_REGISTER, 15);                // Tell it we're setting the low cursor byte.
    hal_outb(VGA_DATA_REGISTER, (uint8_t)position); // Actually set it.
}

/*
 * Very basic function for printing text.
 *
 * TODO: Scrolling?
 */
void hal_basic_display_print(const char *string)
{
    static char *video = 0;

    uint16_t text_index;
    uint16_t color_index;

    if (video == 0) {
        video = (char*)VIDEO_RAM;
    }

    for (; 0 != *string; string++)
    {
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
                row = 0; // TODO: deal with scrolling.
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
    // NOTE: uint16_t will always work, because VIDEO_HEIGHT and VIDEO_WIDTH
    //       are constant with the VGA display mode we're using here.
    uint16_t buf_size = sizeof(char) * VIDEO_HEIGHT * VIDEO_WIDTH;
    char spaces[buf_size + 1];
    spaces[buf_size - 1] = 0;

    for (uint16_t i = 0; i <= buf_size; i++) {
        spaces[i] = ' ';
    }

    hal_basic_display_print(spaces);
    row = 0;
    col = 0;
    hal_basic_display_move_cursor(row, col);
}
