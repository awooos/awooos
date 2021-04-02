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
    //double tmp_d;
    unsigned int tmp_u;
    unsigned long long tmp_ull;

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
        tmp_u = va_arg(args, unsigned int);
        return ali_sprintnu(
            str, size, 1 /* min_length */,
            tmp_u, 16 /* base */, SP_UPPER /* flags */, 1 /* precision */
        );
    /*
    case 'f': {
        // Decimal floating point, lowercase.
        tmp_d = va_arg(args, double);
        break;
    }
    case 'F': {
        // Decimal floating point, uppercase.
        tmp_d = va_arg(args, double);
        break;
    }
    case 'e': {
        // Scientific notation (mantissa/exponent), lowercase.
        tmp_d = va_arg(args, double);
        break;
    }
    case 'E': {
        // Scientific notation (mantissa/exponent), uppercase.
        tmp_d = va_arg(args, double);
        break;
    }
    case 'g': {
        // Use the shortest representation: %e or %f.
        tmp_d = va_arg(args, double);
        int len_e = snprintf(NULL, 0, "%e", tmp_d);
        int len_f = snprintf(NULL, 0, "%f", tmp_d);
        if (len_e <= len_f) {
            // TODO: use %e
        } else {
            // TODO: use %f
        }
        break;
    }
    case 'G': {
        // Use the shortest representation: %E or %F.
        tmp_d = va_arg(args, double);
        int len_E = snprintf(NULL, 0, "%E", tmp_d);
        int len_F = snprintf(NULL, 0, "%F", tmp_d);
        if (len_E <= len_F) {
            // TODO: use %e
        } else {
            // TODO: use %f
        }
        break;
    }
    case 'a': {
        // Hexadecimal floating point, lowercase.
        tmp_d = va_arg(args, double);
        break;
    }
    case 'A': {
        // Hexadecimal floating point, uppercase.
        tmp_d = va_arg(args, double);
        break;
    }
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
    case 'p': {
        // Pointer address.
        // Unsigned hexadecimal integer, lowercase.
        tmp_ull = (unsigned long)va_arg(args, void*);
        return ali_sprintnu(
            str, size, 1 /* min_length */,
            tmp_ull, 16 /* base */, SP_NONE /* flags */, 1 /* precision */
        );
    }
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
