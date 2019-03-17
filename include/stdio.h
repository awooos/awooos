#ifndef ALI_STDIO_H
#define ALI_STDIO_H

#include <stddef.h>

/* References
 * =========
 *
 * http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1548.pdf
 *
 */

typedef size_t FILE;
typedef size_t fpos_t;

// Disable warnings/errors for reserved ID macros, so we can define some.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"

// _IO*BF expand to integer constant expressions with distinct values,
// suitable for use as the third argument to the +setvbuf+ function.
#define _IOFBF 0 // Fully buffered.
#define _IOLBF 1 // Line buffered.
#define _IONBF 2 // Not buffered.

// Re-enable warnings/errors for reserved ID macros.
#pragma clang diagnostic pop

// Integer constant expression that is the size of the buffer used by the
// +setvbuf+ function.
//#define BUFSIZE ??

// Integer constant expression, with type +int+ and negative value, that
// is returned by several functions to indicate end-of-file.
#define EOF (-1)

// Integer constant expression that is the minimum number of files that
// the implementation guarantees can be open simultaneously.
//#define FOPEN_MAX ??

// Integer constant expression that is the size needed for an array of
// +char+ large enough to hold the longest file name string that the
// implementation guarantees can be opened.
//#define FILENAME_MAX ??

// Integer constant expression that is the size needed for an array of
// +char+ large enough to hold a temporary file name string generated by
// the +tmpnam+ function.
//#define L_tmpnam ??

// Integer constant expressions with distinct values, suitable for use as
// the third argument to the +fseek+ function.
//#define SEEK_CUR 0
//#define SEEK_END 1
//#define SEEK_SET 2

// Integer constant expression that is the minimum number of unique file
// names that can be generated by the tmpnam function.
//#define TMP_MAX ??

// Expressions of type "pointer to FILE" that point to the FILE objects
// associated, respectively, with the standard error, input, and output
// streams.
//
// FIXME: Actually implement streams.
//extern FILE *stdin;
//extern FILE *stdout;
//extern FILE *stderr;
// HACK: These are gauranteed-distinct, but don't provide any actual information.
static FILE *stdin  = (FILE*)0;
static FILE *stdout = (FILE*)1;
static FILE *stderr = (FILE*)2;

int fputc(int c, FILE *stream);
int putc(int c, FILE *stream);
int putchar(int c);

int fputs(const char *string, FILE *stream);
int puts(const char *string);

#endif
