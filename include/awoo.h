#ifndef AWOO_H
#define AWOO_H

#include <awoo/build_info.h>

// Disable warnings/errors for reserved ID macros, so we can define some.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"
    // Define said macros.
    #define __awoo__

    #define AWOO_VERSION AWOO_SCM_REV"-"AWOO_BUILD_TYPE

    #define __AWOO_INFO__ "awooOS "AWOO_TARGET" "AWOO_VERSION
#pragma clang diagnostic pop

static const char *AWOO_INFO = __AWOO_INFO__;

#endif
