#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <eventually.h>


// ASSUMPTION: No more than 50 events, and no more than 50 handlers per event.

static EvEventGroup event_groups[EVENTUALLY_MAX_EVENT_GROUPS + 1] = {
    NULL, NULL, NULL, NULL, NULL, /*  5 */ NULL, NULL, NULL, NULL, NULL, /* 10 */
    NULL, NULL, NULL, NULL, NULL, /* 15 */ NULL, NULL, NULL, NULL, NULL, /* 20 */
    NULL, NULL, NULL, NULL, NULL, /* 25 */ NULL, NULL, NULL, NULL, NULL, /* 30 */
    NULL, NULL, NULL, NULL, NULL, /* 35 */ NULL, NULL, NULL, NULL, NULL, /* 40 */
    NULL, NULL, NULL, NULL, NULL, /* 45 */ NULL, NULL, NULL, NULL, NULL, /* 50 */
    NULL,
};

static bool initialized = false;
static size_t number_of_events = 0;

EvEventGroup *eventually_find_group(const char *event_name)
{
    EvEventGroup *group = &(event_groups[0]);

    for (; group != NULL; group++) {
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

    group = &(event_groups[number_of_events + 1]);

    memset(group, 0, sizeof(EvEventGroup));

    group->name = event_name;

    return group;
}

bool eventually_add_handler(const char *event_name, EvEventHandler *handler)
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

bool eventually_trigger_event(const char *event_name, void *data)
{
    EvEventGroup *group = eventually_find_group(event_name);

    // If no group is found, return false.
    if (group == NULL) {
        return false;
    }

    for (size_t i = 0; i < group->number_of_handlers; i++) {
        group->handlers[i](event_name, data);
    }

    return true;
}

