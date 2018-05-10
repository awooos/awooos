#include <ali/str.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "split.h"

ShellSplitResult *shellsplit(char *input)
{
    ShellSplitResult *result = malloc(sizeof(ShellSplitResult));
    char *str = input;
    size_t len = strlen(str); 
    char *buffer = ali_malloc(len);

    memset(result, 0, sizeof(ShellSplitResult));

    // Storage for pieces
    size_t piece_idx = 0;
    size_t piece_length = 0;
    char **pieces = ali_malloc(sizeof(char *) * ALI_SPLIT_MAX_PIECES);
    for (size_t i = 0; i < ALI_SPLIT_MAX_PIECES; i++) {
        pieces[i] = NULL;
    }

    // Flags
    size_t in_doublequote = 0;
    size_t in_singlequote = 0;
    size_t in_escape = 0;

    for (size_t i = 0; i < len; i++) {
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
                buffer = ali_malloc((len - i) + 1);
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

    result->pieces = pieces;
    result->num_pieces = piece_idx;

    return result;
}
