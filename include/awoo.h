#ifndef AWOO_H
#define AWOO_H

#include <awoo/build_info.h>

#define __awoo__

#define AWOO_VERSION AWOO_SCM_REV"-"AWOO_BUILD_TYPE

#define __AWOO_INFO__ "awooOS "AWOO_TARGET" "AWOO_VERSION
static const char *AWOO_INFO = __AWOO_INFO__;

#endif
