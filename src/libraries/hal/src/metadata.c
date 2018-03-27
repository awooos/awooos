#include <ali/modifiers.h>
#include <kernel.h>
#include "metadata.h"

extern char kernel_comment_start;

char *hal_metadata_compiler_information()
{
    return &kernel_comment_start;
}

void hal_metadata_print(UNUSED const char *event_name, UNUSED void *data,
        UNUSED size_t data_size)
{
    kprint("\r\nCompiled with ");
    kprint(hal_metadata_compiler_information());
}
