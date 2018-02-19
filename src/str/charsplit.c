#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "split.h"

char **charsplit(char *input, char token)
{
    char *str = input;
    int len = strlen(str); 
    char *buffer = malloc(len);

    // Storage for pieces
    int piece_idx = 0;
    int piece_length = 0;
    char **pieces = malloc(sizeof(char *) * ALI_SPLIT_MAX_PIECES);
    for (int i = 0; i < ALI_SPLIT_MAX_PIECES; i++) {
        pieces[i] = NULL;
    }

    for (int i = 0; i < len; i++) {
        char c = *str;
        buffer[piece_length] = c;

        if (c == token) {
            buffer[piece_length] = 0;
            pieces[piece_idx] = buffer;
            buffer = malloc((len - i) + 1);
            piece_length = 0;
            piece_idx++;
            str++;
        }

        str++;
        piece_length++;
    }

    buffer[piece_length] = 0;
    pieces[piece_idx] = buffer;

    return pieces;
}
