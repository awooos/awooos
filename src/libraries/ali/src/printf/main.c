#include <stdarg.h>
#include <stdio.h>

int snprintf(char *str, size_t size, const char *fmt, ...) {
    va_list args;
    int len;

    va_start(args, fmt);
    len = vsnprintf(str, size, fmt, args);
    va_end(args);

    return len;
}

int sprintf(char *str, const char *fmt, ...) {
    va_list args;
    int len;

    va_start(args, fmt);
    len = vsprintf(str, fmt, args);
    va_end(args);

    return len;
}

int printf(const char *fmt, ...) {
    va_list args;
    int len = 0;

    va_start(args, fmt);
    len = vprintf(fmt, args);
    va_end(args);

    return len;
}
