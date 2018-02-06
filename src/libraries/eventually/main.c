#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <eventually.h>

// ASSUMPTION: No more than 50 events, and no more than 50 handlers per event.

static EvEventGroup event_groups[EVENTUALLY_MAX_EVENT_GROUPS + 1] = {
    0, 0, 0, 0, 0, /*  5 */ 0, 0, 0, 0, 0, /* 10 */
    0, 0, 0, 0, 0, /* 15 */ 0, 0, 0, 0, 0, /* 20 */
    0, 0, 0, 0, 0, /* 25 */ 0, 0, 0, 0, 0, /* 30 */
    0, 0, 0, 0, 0, /* 35 */ 0, 0, 0, 0, 0, /* 40 */
    0, 0, 0, 0, 0, /* 45 */ 0, 0, 0, 0, 0, /* 50 */
    NULL,
};

static bool initialized = false;
static size_t number_of_events = 0;

EvEventGroup *eventually_find_group(const char *event_name)
{
    EvEventGroup *group;

    for (size_t i = 0; i < number_of_events; i++){
        group = &(event_groups[i]);

        if (strcmp(event_name, group->name) == 0) {
            return group;
        }
    }

    return NULL;
}

EvEventGroup *eventually_create_group(const char *event_name)
{
    EvEventGroup *group;

    // Too many events. :(
    if (number_of_events > EVENTUALLY_MAX_EVENT_GROUPS) {
        return NULL;
    }

    group = &(event_groups[number_of_events]);

    memset(group, 0, sizeof(EvEventGroup));

    group->name = event_name;
    number_of_events++;

    return group;
}

bool event_watch(const char *event_name, EvEventHandler *handler)
{
    EvEventGroup *group = eventually_find_group(event_name);

    // If there's no group for this event, let's make one.
    if (group == NULL) {
        group = eventually_create_group(event_name);
    }

    // If we failed to make one, return false.
    if (group == NULL) {
        return false;
    }


    // If there's too many handlers, return false.
    if (group->number_of_handlers > EVENTUALLY_MAX_HANDLERS_PER_GROUP) {
        return false;
    }

    group->handlers[group->number_of_handlers] = handler;
    group->number_of_handlers++;

    return true;
}

bool event_trigger(const char *event_name, void *data, size_t data_size)
{
    EvEventGroup *group = eventually_find_group(event_name);
    void *tmp_data;

    // If no group is found, return false.
    // If there's no registered event handlers, return false.
    if (group == NULL || group->number_of_handlers == 0) {
        return false;
    }

    for (size_t i = 0; i < group->number_of_handlers; i++) {
        if (data != NULL && data_size != 0) {
            // If data and size is provided, then copy it.
            tmp_data = malloc(data_size);
            memcpy(tmp_data, data, data_size);
        } else if (data != NULL && data_size == 0) {
            // If data is provided, but size is not, assign it directly.
            tmp_data = data;
        } else {
            // Otherwise, give them NULL.
            tmp_data = NULL;
            data_size = 0;
        }

        group->handlers[i](event_name, tmp_data, data_size);
    }

    return true;
}

// Can be replaced with a not-immediate variant later on, if wanted.
bool event_trigger_async(const char *event_name, void *data, size_t data_size)
{
    return event_trigger(event_name, data, data_size);
}
