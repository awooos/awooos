#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "sprintn.h"

int ali_vprint_arg(char *str, size_t size, const char *format, int *consumed, va_list args) {
    // Changing the value of *consumed will change `format` for the
    // next iteration. This is useful for, e.g., making sure all of the
    // characters in things like `%.2f` get consumed -- not just the %.
    (void)consumed; // this isn't actually used yet.

    char tmp_c;
    int tmp_i;
    unsigned int tmp_u;

    const char *p = format;

    switch (*p) {
    case 'd':
    case 'i':
        // Signed decimal integer.
        tmp_i = va_arg(args, int);
        return ali_sprintni(
            str, size, 1 /* min_length */,
            tmp_i, 10 /* base */, 0 /* flags */, 1 /* precision */
        );
    case 'u':
        // Unsigned decimal integer.
        tmp_u = va_arg(args, unsigned int);
        return ali_sprintnu(
            str, size, 1 /* min_length */,
            tmp_u, 10 /* base */, 0 /* flags */, 1 /* precision */
        );
    case 'o':
        // Unsigned octal.
        tmp_u = va_arg(args, unsigned int);
        return ali_sprintnu(
            str, size, 1 /* min_length */,
            tmp_u, 8 /* base */, 0 /* flags */, 1 /* precision */
        );
    case 'x':
        // Unsigned hexadecimal integer, lowercase.
        tmp_u = va_arg(args, unsigned int);
        return ali_sprintnu(
            str, size, 1 /* min_length */,
            tmp_u, 16 /* base */, 0 /* flags */, 1 /* precision */
        );
    case 'X':
        // Unsigned hexadecimal integer, uppercase.
        // TODO: Make this uppercase.
        tmp_u = va_arg(args, unsigned int);
        return ali_sprintnu(
            str, size, 1 /* min_length */,
            tmp_u, 16 /* base */, 0 /* flags */, 1 /* precision */
        );
    /*
    case 'f':
        // Decimal floating point, lowercase.
        va_arg(args, double);
        break;
    case 'F':
        // Decimal floating point, uppercase.
        va_arg(args, double);
        break;
    case 'e':
        // Scientific notation (mantissa/exponent), lowercase.
        va_arg(args, double);
        break;
    case 'E':
        // Scientific notation (mantissa/exponent), uppercase.
        va_arg(args, double);
        break;
    case 'g':
        // Use the shortest representation: %e or %f.
        va_arg(args, double);
        break;
    case 'G':
        // Use the shortest representation: %E or %F.
        va_arg(args, double);
        break;
    case 'a':
        // Hexadecimal floating point, lowercase.
        va_arg(args, double);
        break;
    case 'A':
        // Hexadecimal floating point, uppercase.
        va_arg(args, double);
        break;
    */
    case 'c':
        // Character.
        tmp_c = (char)va_arg(args, int);
        if (str) {
            str[0] = tmp_c;
        }
        return 1;
    case 's': {
        // String of characters.
        const char *tmp_s = va_arg(args, const char*);
        size_t tmp_s_len = strlen(tmp_s);

        if (size < tmp_s_len) {
            return -1;
        }

        if (str) {
            strncpy(str, tmp_s, tmp_s_len);
        }
        return (int)tmp_s_len;
    }
    /*
    case 'p':
        // Pointer address.
        va_arg(args, unsigned int);
        break;
    */
    case 'n':
        // Nothing printed.
        return 0;
    case '%':
        // A literal %.
        str[0] = '%';
        return 1;
    }

    return -1;
}
