// POSIX SPEC VIOLATION: We always define assert(), even though the POSIX
//                       standard dictates that it should be redefined
//                       to either a no-op or the normal implementation
//                       _every time assert.h is included_ based on the
//                       existence of the NDEBUG macro.
//
//                       Details: http://en.cppreference.com/w/c/error/assert
//
//                       I decided it was not worth the effort, given the
//                       complexity of doing so and this quote from Linux's
//                       `man assert` (aka the Linux Programmer's Manual):
//                          "It is not recommended to define NDEBUG if
//                           using assert()"
//
//                       If you disagree with my decision, please _do not
//                       hesitate_ to open an issue on GitHub!
//                          https://github.com/awooos/ali/issues
//
//                       - @duckinator, 2018-02-20

#ifndef ASSERT_H
#define ASSERT_H

extern void __ali_assert_fail(const char *expr, const char *file,
                                unsigned int line, const char *func);

#define assert(expr) ((expr) || __ali_assert_fail(#expr, __FILE__, __LINE__, __func__))
#define static_assert _Static_assert

#endif
