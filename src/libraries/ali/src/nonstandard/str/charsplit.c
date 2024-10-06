#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "split.h"

char **charsplit(char *input, char token)
{
    char *str = input;
    size_t len = strlen(str);
    char *buffer = malloc(len + 1);

    memcpy(buffer, input, len);
    buffer[len] = 0; // Add a null terminator, just to be sure.

    // Pointers to individual pieces.
    size_t piece_idx = 0;
    char **pieces = calloc(ALI_SPLIT_MAX_PIECES, sizeof(char*));

    pieces[piece_idx] = buffer;
    piece_idx++;

    for (size_t idx = 0; idx < len; idx++) {
        if (buffer[idx] == token) {
            buffer[idx] = 0;
            pieces[piece_idx] = (buffer + idx + 1);
            piece_idx++;
        }
    }

    return pieces;
}
