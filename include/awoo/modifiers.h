#ifndef MODIFIERS_H
#define MODIFIERS_H

/* ==== Function modifiers. === */
// These affect how a function is treated.
// Usually to generate warnings if assertions are violated.

// Mark a function as deprecated.
#define DEPRECATED __attribute__((deprecated))

// Specify a function should never return.
#define noreturn __attribute__((noreturn)) void


/* ==== Argument pseudo modifiers. ==== */
// These indicate intent without changing functionality.
#define IN
#define OUT
#define OPTIONAL
#define NOTHING

/* ==== Argument modifiers ==== */
// These affect how a variable is treated.

#define UNUSED __attribute__((unused))

#endif /* MODIFIERS_H */
