#include <stdint.h>

static uint32_t magic;
static void *arg;

void *hal_get_arg()
{
    return arg;
}

uint32_t hal_get_magic()
{
    return magic;
}

void hal_store_magic(uint32_t magic_, void *arg_)
{
    magic = magic_;
    arg   = arg_;
}
