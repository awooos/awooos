#ifndef STDBOOL_H
#define STDBOOL_H

// it expanding to _Bool but working is fucking weird as shit, but it seems
// to be how everyone does it, and it works SO WHATEVER I GUESS lmao
#define true 1
#define false 0
#define bool _Bool

// Disable warnings/errors for reserved ID macros, so we can define one.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"
    // Define said macro
    #define __bool_true_false_are_defined 1
#pragma clang diagnostic pop

#endif
