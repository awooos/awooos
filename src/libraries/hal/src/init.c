#include <ali.h>
#include <ali/event.h>
#include <dmm.h>
#include "metadata.h"

void hal_init(void *data)
{
    ali_init(&_dmm_malloc, &_dmm_free, &_dmm_realloc);
    event_trigger("greeter display", hal_metadata);
}
