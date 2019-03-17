#include <stdio.h>
#include <ali/text.h>
#include <ali/event.h>

// Writes the provided character (+c+) to the provided stream (+stream+).
//
// Returns EOF on write error, or +c+ otherwise.
//
// FIXME: Actually handle streams.
int fputc(int c, FILE *stream)
{
    (void)stream;

    /* Start hacky bullshit */
    char str[2] = {(unsigned char)character, 0};
    event_trigger("print string", (char*)str);
    /* End hacky bullshit */

    return c;
}

// Writes the provided string (+s+) to the provided stream (+stream+).
// The terminating null character is not written.
//
// Returns EOF on write error, or a non-negative value on success.
//
// FIXME: Actually handle streams.
int fputs(const char *s, FILE *stream)
{
    /* Start hacky bullshit */
    event_trigger("print string", (char*)str);
    event_trigger("print string", "\n");
    /* End hacky bullshit */

    return 1;
}

// Writes the provided string (+s+) to stdout.
//
// Returns EOF on write error, or a non-negative value on success.
int puts(const char *s)
{
    return fputs(s, stdout);
}

// TODO: Remove print().
char *print(const char *string)
{
    event_trigger("print string", (char*)string);

    return (char*)string;
}

// TODO: Remove println().
char *println(const char *string)
{
    puts(string);

    return (char*)string;
}
