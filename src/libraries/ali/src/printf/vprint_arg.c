#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "sprintn.h"
#include "vprintf.h"

//void xxputs(const char *str) { while(*str) { putchar(*str++); } }

void _ali_vprint_parse_flags(VprintFlags *flags, const char *format, int *consumed) {
    if (!format[0]) {
        // If there's nothing left, bail.
        return;
    }

    for (int i = 0; format[i]; i++) {
        switch(format[i]) {
        // POSIX adds support for a ' flag, e.g. %'i.
        // This is not part of the C standard, so it is (at least for now)
        // unimplemented.
        //case '\'':
        //    ...
        case '-':
            *consumed += 1;
            flags->left_justified = 1;
            break;
        case '+':
            *consumed += 1;
            flags->always_show_sign = 1;
            break;
        case ' ':
            *consumed += 1;
            flags->space_if_positive = 1;
            break;
        case '#':
            *consumed += 1;
            flags->alt_form = 1;
            break;
        case '0':
            *consumed += 1;
            flags->leading_zeros = 1;
            break;
        default:
             // If none of the other options match, it's not a flag.
            return;
        }
    }
}

void _ali_vprint_parse_length_modifier(VprintLengthModifier *mod, const char *format, int *consumed) {
    if (!format[0]) {
        // If there's nothing left, bail.
        return;
    }

    switch (*format) {
    case 'h':
        if (format[1] == 'h') {
            *consumed += 2;
            mod->hh = 1;
        } else {
            *consumed += 1;
            mod->h = 1;
        }
        break;
    case 'l':
        if (format[1] == 'l') {
            *consumed += 2;
            mod->ll = 1;
        } else {
            *consumed += 1;
            mod->l = 1;
        }
        break;
    case 'j':
        *consumed += 1;
        mod->j = 1;
        break;
    case 'z':
        *consumed += 1;
        mod->z = 1;
        break;
    case 't':
        *consumed += 1;
        mod->t = 1;
        break;
    case 'L':
        *consumed += 1;
        mod->L = 1;
        break;
    default:
        // If none of the other options match, it's not a length modifier.
        return;
    }
}

void _ali_vprint_parse_conversion_specifier(VprintConversionSpecifier *vspec, const char *format, int *consumed) {
    if (!format[0]) {
        // If there's nothing left, bail.
        return;
    }

    switch (*format) {
    case 'd':
    case 'i':
        *consumed += 1;
        vspec->d = 1;
        vspec->i = 1;
        break;
    case 'o':
        *consumed += 1;
        vspec->o = 1;
        break;
    case 'u':
        *consumed += 1;
        vspec->u = 1;
        break;
    case 'x':
        *consumed += 1;
        vspec->x = 1;
        break;
    case 'X':
        *consumed += 1;
        vspec->X = 1;
        break;
    case 'f':
        *consumed += 1;
        vspec->f = 1;
        break;
    case 'F':
        *consumed += 1;
        vspec->F = 1;
        break;
    case 'e':
        *consumed += 1;
        vspec->e = 1;
        break;
    case 'E':
        *consumed += 1;
        vspec->E = 1;
        break;
    case 'g':
        *consumed += 1;
        vspec->g = 1;
        break;
    case 'G':
        *consumed += 1;
        vspec->G = 1;
        break;
    case 'a':
        *consumed += 1;
        vspec->a = 1;
        break;
    case 'A':
        *consumed += 1;
        vspec->A = 1;
        break;
    case 'c':
        *consumed += 1;
        vspec->c = 1;
        break;
    case 's':
        *consumed += 1;
        vspec->s = 1;
        break;
    case 'p':
        *consumed += 1;
        vspec->p = 1;
        break;
    case 'n':
        *consumed += 1;
        vspec->n = 1;
        break;
    // POSIX adds support for C and S conversion specifiers.
    // These are not part of the C standard so they are, at least for now,
    // not being implemented.
    case '%':
        *consumed += 1;
        vspec->percent = 1;
        break;
    default:
        // If none of the other options match, it's not a conversion specifier.
        return;
    }
}

int ali_vprint_arg(char *str, size_t size, const char *format, int *consumed, va_list args, int length) {
    // Changing the value of *consumed will change `format` for the
    // next iteration. This is useful for, e.g., making sure all of the
    // characters in things like `%.2f` get consumed -- not just the %.

    char tmp_c;
    int tmp_i;
    //double tmp_d;
    unsigned int tmp_u;
    unsigned long long tmp_ull;

    VprintFlags flags = {0};
    VprintLengthModifier mod = {0};
    VprintConversionSpecifier vspec = {0};

    _ali_vprint_parse_flags(&flags, format, consumed);
    _ali_vprint_parse_length_modifier(&mod, format, consumed);
    _ali_vprint_parse_conversion_specifier(&vspec, format, consumed);


    if (vspec.d || vspec.i) {
        // Signed decimal integer.
        tmp_i = va_arg(args, int);
        return ali_sprintni(
            str, size, 1 /* min_length */, tmp_i,
            10 /* base */, &flags, 0 /* upper */, 1 /* precision */
        );
    } else if (vspec.o) {
         // Unsigned octal.
        tmp_u = va_arg(args, unsigned int);
        return ali_sprintnu(
            str, size, 1 /* min_length */, tmp_u,
            8 /* base */, &flags, 0 /* upper */, 1 /* precision */
        );
    } else if (vspec.u) {
        // Unsigned decimal integer.
        tmp_u = va_arg(args, unsigned int);
        return ali_sprintnu(
            str, size, 1 /* min_length */, tmp_u,
            10 /* base */, &flags, 0 /* upper */, 1 /* precision */
        );
    } else if (vspec.x || vspec.X) {
        // Unsigned hexadecimal integer. x = lowercase, X = uppercase.
        tmp_u = va_arg(args, unsigned int);
        return ali_sprintnu(
            str, size, 1 /* min_length */, tmp_u,
            16 /* base */, &flags, vspec.X /* upper */, 1 /* precision */
        );
    //} else if (vspec.f || vspec.F) {
    //    // Decimal floating point. f = lowercase, F = uppercase.
    //    tmp_d = va_arg(args, double);
    //    return ali_sprintnd(
    //        str, size, 1 /* min_length */, tmp_d,
    //        10 /* base */, &flags, vspec.F /* upper */, 1 /* precision */
    //    );
    //} else if (vspec.e || vspec.E) {
    //    // Decimal floating point, scientific notation. e = lowercase, E = uppercase.
    //    tmp_d = va_arg(args, double);
    //    return ali_sprintnd(
    //        str, size, 1 /* min_length */, tmp_d,
    //        10 /* base */, &flags, vspec.E /* upper */, 1 /* precision */
    //    );
    //} else if (vspec.g || vspec.G) {
    //    // Decimal floating point, f or e/F or E, it's complicated
    //} else if (vspec.a || vspec.A) {
    //    // Hexadecimal floating point, scientific notation.
    //    tmp_d = va_arg(args, double);
    //    return ali_sprintnd(
    //        str, size, 1 /* min_length */, tmp_d,
    //        10 /* base */, &flags, vpsec.A /* upper */, 1 /* precision */
    //    );
    } else if (vspec.c) {
        // The +int+ argument is converted to an +unsigned char+, and
        // the resulting byte is written.
        // TODO: Support the l (ell) qualifier.
        tmp_c = (char)va_arg(args, int);
        if (str) {
            str[0] = tmp_c;
        }
        return 1;
    } else if (vspec.s) {
        // String of characters.
        // TODO: Support the l (ell) qualifier.
        const char *tmp_s = va_arg(args, const char*);
        size_t tmp_s_len = strlen(tmp_s);

        if (size < tmp_s_len) {
            return -1;
        }

        if (str) {
            strncpy(str, tmp_s, tmp_s_len);
        }
        return (int)tmp_s_len;
    } else if (vspec.p) {
        // Pointer to avoid.
        // Unsigned hexadecimal integer, lowercase.
        tmp_ull = (unsigned long)va_arg(args, void*);
        return ali_sprintnu(
            str, size, 1 /* min_length */, tmp_ull,
            16 /* base */, &flags, 0 /* uppercase */, 1 /* precision */
        );
    } else if (vspec.n) {
        // The argument is a pointer to an int. The number of bytes written
        // to the output so far is written to it.
        // Nothing is printed.
        int *tmp_intptr = va_arg(args, int*);
        *tmp_intptr = length;
        return 0;
    } else if (vspec.percent) {
        // A literal %.
        str[0] = '%';
        return 1;
    }

    return -1;
}
