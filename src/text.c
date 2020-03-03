#include <stdio.h>
#include <ali/text.h>
#include <ali/event.h>

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
    event_trigger("print string", (char*)str);
    /* End hacky bullshit */

    return c;
}

int putc(int c, FILE *stream)
{
    return fputc(c, stream);
}

int putchar(int c)
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
    event_trigger("print string", (char*)s);
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

// TODO: Remove print().
char *print(const char *string)
{
    event_trigger("print string", (char*)string);

    return (char*)string;
}
