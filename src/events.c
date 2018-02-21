#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ali/events.h>

// ASSUMPTION: No more than 50 events, and no more than 50 handlers per event.

static AliEventGroup event_groups[ALI_EVENT_MAX_EVENT_GROUPS + 1] = {
    0, 0, 0, 0, 0, /*  5 */ 0, 0, 0, 0, 0, /* 10 */
    0, 0, 0, 0, 0, /* 15 */ 0, 0, 0, 0, 0, /* 20 */
    0, 0, 0, 0, 0, /* 25 */ 0, 0, 0, 0, 0, /* 30 */
    0, 0, 0, 0, 0, /* 35 */ 0, 0, 0, 0, 0, /* 40 */
    0, 0, 0, 0, 0, /* 45 */ 0, 0, 0,
    NULL,
};

static size_t number_of_events = 0;

AliEventGroup *_ali_event_create_group(const char *event_name)
{
    AliEventGroup *group;

    // Too many events. :(
    if (number_of_events > ALI_EVENT_MAX_EVENT_GROUPS) {
        return NULL;
    }

    group = &(event_groups[number_of_events]);

    memset(group, 0, sizeof(AliEventGroup));

    group->name = event_name;
    number_of_events++;

    return group;
}

AliEventGroup *_ali_event_find_or_create_group(const char *event_name)
{
    AliEventGroup *group;

    for (size_t i = 0; i < number_of_events; i++){
        group = &(event_groups[i]);

        if (strcmp(event_name, group->name) == 0) {
            return group;
        }
    }

    // If we get here, there's no group — so make one!
    return _ali_event_create_group(event_name);
}

bool event_watch(const char *event_name, AliEventHandler *handler)
{
    AliEventGroup *group = _ali_event_find_or_create_group(event_name);

    // If we couldn't find or create a group, return false.
    if (group == NULL) {
        return false;
    }

    // If there's too many handlers, return false.
    if (group->number_of_handlers > ALI_EVENT_MAX_HANDLERS_PER_GROUP) {
        return false;
    }

    group->handlers[group->number_of_handlers] = handler;
    group->number_of_handlers++;

    return true;
}

bool event_trigger(const char *event_name, void *data, size_t data_size)
{
    AliEventGroup *group = _ali_event_find_or_create_group(event_name);
    void *tmp_data;

    // If no group is found, return false.
    if (group == NULL) {
        return false;
    }

    for (size_t i = 0; i < group->number_of_handlers; i++) {
        if (data != NULL && data_size != 0) {
            // If data and size is provided, then copy it.
            tmp_data = malloc(data_size);
            memcpy(tmp_data, data, data_size);
        } else {
            // Otherwise, pass the originals.
            tmp_data = data;
            data_size = 0;
        }

        group->handlers[i](event_name, tmp_data, data_size);
    }

    return true;
}
