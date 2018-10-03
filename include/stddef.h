#ifndef STDDEF_H
#define STDDEF_H

/* References
 * =========
 *
 * http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1548.pdf
 * https://sourceforge.net/p/predef/wiki/Standards/
 *
 * To generate a list of predefined macros:
 * clang -std=c11 -m32 -nostdinc -ffreestanding -dM -E -x c /dev/null
 *
 * TODO: Add standard macros.
 *
 */


// I can dream.
//#define __STDC_VERSION__ 201112L // C11

#define NULL ((void*)0)
//#define offsetof(type, member_designator) TODO

typedef __PTRDIFF_TYPE__ ptrdiff_t;
typedef __SIZE_TYPE__ size_t;
// TODO: ssize_t?
typedef __WCHAR_TYPE__ wchar_t;

#endif /* STDDEF_H */

