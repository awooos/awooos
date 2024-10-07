#include <stdio.h>
#include <hal.h>

// Writes the provided character (+c+) to the provided stream (+stream+).
//
// +c+ is cast to an unsigned char internally.
//
// Returns EOF on write error, or +c+ otherwise.
//
// FIXME: Actually handle streams.
int fputc(int c, FILE *stream)
{
    (void)stream;

    /* Start hacky bullshit */
    char str[2] = {(char)c, 0};
    hal_print((char*)str);
    /* End hacky bullshit */

    return c;
}

int putc(int c, FILE *stream)
{
    return fputc(c, stream);
}

// HACK: When testing things outside of a kernel, defining `putchar()`
//       breaks everything.
#ifdef ALI_PUTCHAR_NAME
int ALI_PUTCHAR_NAME(int c)
#else
int putchar(int c)
#endif
{
    return putc(c, stdout);
}

// Writes the provided string (+s+) to the provided stream (+stream+).
// The terminating null character is not written.
//
// Returns EOF on write error, or a non-negative value on success.
//
// FIXME: Actually handle streams.
int fputs(const char *s, FILE *stream)
{
    (void)stream;

    /* Start hacky bullshit */
    hal_print((char*)s);
    /* End hacky bullshit */

    return 1;
}

/// Writes the provided string (@p s) and a trailing newline to stdout.
///
/// Returns EOF on write error, or a non-negative value on success.
int puts(const char *s)
{
    if (fputs(s, stdout) < 0) {
        return EOF;
    }
    return fputs("\n", stdout);
}
