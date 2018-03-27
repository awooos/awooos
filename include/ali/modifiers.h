#ifndef ALI_MODIFIERS_H
#define ALI_MODIFIERS_H

#include <stdnoreturn.h>

/* ==== Function modifiers. === */
// These affect how a function is treated.
// Usually to generate warnings if assertions are violated.

// Mark a function as deprecated.
#define DEPRECATED __attribute__((deprecated)

/* ==== Function pseudo modifiers. ==== */
// These indicate intent without changing functionality.
#define MAY_PANIC
#define NONSTANDARD
#define PARTIAL_IMPLEMENTATION
#define UNTESTED

/* ==== Argument pseudo modifiers. ==== */
// These indicate intent without changing functionality.
#define IN
#define OUT
#define OPTIONAL
#define NOTHING

/* ==== Argument modifiers ==== */
// These affect how a variable is treated.
#define UNUSED __attribute__((unused))

#endif /* ALI_MODIFIERS_H */
