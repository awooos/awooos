#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "split.h"

char **shellsplit(char *input)
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

    // Flags
    int in_doublequote = 0;
    int in_singlequote = 0;
    int in_escape = 0;

    for (int i = 0; i < len; i++) {
        char c = *str;
        buffer[piece_length] = c;

        switch (c) {
            case '"':
                if (in_escape == 0) {
                    in_doublequote = (in_doublequote == 0 ? 1 : 0);
                    str++;
                    continue;
                } else {
                    in_escape = 0;
                }

                break;

            case '\'':
                if (in_escape == 0) {
                    in_singlequote = (in_singlequote == 0 ? 1 : 0);
                    str++;
                    continue;
                } else {
                    in_escape = 0;
                }

                break;

            case '\\':
                in_escape = (in_escape == 0 ? 1 : 0);
                if (in_escape == 1) {
                    str++;
                }

                continue;

            case ' ':
                if (in_escape == 1) {
                    in_escape = 0;
                    break;
                }

                if (in_singlequote == 1 || in_doublequote == 1) {
                    break;
                }

                buffer[piece_length] = 0;
                pieces[piece_idx] = buffer;
                buffer = malloc((len - i) + 1);
                piece_length = 0;
                piece_idx++;
                str++;

                continue;

            default:
                if (in_escape == 1) {
                    in_escape = 0;
                }

                break;
        }

        str++;
        piece_length++;
    }

    buffer[piece_length] = 0;
    pieces[piece_idx] = buffer;

    return pieces;
}
