#include <ali/modifiers.h>
#include <ali/text.h>
#include <hal.h>
#include "metadata.h"

extern char kernel_comment_start;

char *hal_metadata_compiler_information()
{
    return &kernel_comment_start;
}

void hal_metadata_print(UNUSED void *data)
{
    print("\r\nCompiled with ");
    print(hal_metadata_compiler_information());
}
