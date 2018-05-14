#ifndef HAL_METADATA_H
#define HAL_METADATA_H

#include <awoo.h>
#include <stddef.h>

extern char kernel_comment_start;

static const char *hal_metadata[] = {
    __AWOO_INFO__ "\r\n",
    "Compiled with: ",
    &kernel_comment_start,
    NULL
};

#endif
