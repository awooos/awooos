#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ali_vprint_arg(char *str, size_t size, const char *format, int *consumed, va_list args);

// NOTE: To debug anything in this file, using `putchar()` is useful.
//       Things like `puts` won't always work here, if running the test suite.
//       xxputs is a basic wrapper around putchar which _does_ work there.
//void xxputs(const char *str) { while(*str) { putchar(*str++); } }

int vsnprintf(char *str, size_t size, const char *format, va_list args) {
    int length = 0;
    int tmp;

    for (const char *p = format; *p; p++) {
        // consumed can be modified in ali_vprint_arg() to adjust the
        // value of `p`, e.g. if there's a modifier (like "%.2f").
        int consumed = 0;

        switch (*p) {
        case '%':
            p++; // Skip the % we just matched.
            tmp = ali_vprint_arg(str + length, size - (size_t)length, p, &consumed, args);
            if (tmp < 0) {
                return length;
            }
            length += tmp;
            p += consumed;
            break;
        /*case '\\':
            // TODO: Handle escaped text.
            break;*/
        default:
            if (((size_t)length < size) && str) {
                str[length] = *p;
            }
            length++;
            break;
        }
    }

    // Add trailing null byte, if the buffer is usable.
    if (size > 0) {
        if ((size_t)length < size) {
            str[length] = '\0';
        } else {
            str[size + 1] = '\0';
        }
    }

    return length;
}

int vsprintf(char *str, const char *format, va_list args) {
    int len;
    len = vsnprintf(NULL, 0, format, args);
    len = vsnprintf(str, (size_t)(len + 1), format, args);
    return len;
}

int vprintf(const char *format, va_list args) {
    char *str;
    int len;

    len = vsnprintf(NULL, 0, format, args);
    len++;

    str = malloc((size_t)len);
    len = vsnprintf(str, (size_t)len, format, args);

    for (size_t idx = 0; str[idx]; idx++) {
        putchar(str[idx++]);
    }

    free(str);

    return len;
}
