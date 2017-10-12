#ifndef STDDEF_H
#define STDDEF_H

/* References
 * =========
 *
 * http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1548.pdf
 * https://sourceforge.net/p/predef/wiki/Standards/
 *
 */


// I can dream.
//#define __STDC_VERSION__ 201112L // C11

#define NULL ((void*)0)

#ifdef __x86_64
    // 8 bytes.
    typedef unsigned long int size_t;
#elif __i386
    // 4 bytes.
    typedef unsigned int size_t;
#endif

#endif /* STDDEF_H */

