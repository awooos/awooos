#ifndef EVENTUALLY_H
#define EVENTUALLY_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef void EvEventHandler(const char *name, void *data, size_t data_size);

#define EVENTUALLY_MAX_EVENT_GROUPS 50
#define EVENTUALLY_MAX_HANDLERS_PER_GROUP 50

typedef struct eventually_event_group {
    const char *name;
    size_t number_of_handlers;
    EvEventHandler *handlers[EVENTUALLY_MAX_HANDLERS_PER_GROUP];
} EvEventGroup;

bool event_watch(const char *event_name, EvEventHandler *handler);
bool event_trigger(const char *event_name, void *data, size_t data_size);
bool event_trigger_async(const char *event_name, void *data, size_t data_size);

#endif
