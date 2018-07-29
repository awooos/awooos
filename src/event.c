#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ali/event.h>

// ASSUMPTION: Maximum ALI_EVENT_MAX_EVENT_GROUPS event groups.
// ASSUMPTION: Maximum ALI_EVENT_MAX_HANDLERS_PER_GROUP handlers per event.

// A collection of event groups, initialized to null bytes.
static AliEventGroup event_groups[ALI_EVENT_MAX_EVENT_GROUPS] = {{0,0,{0}}};

static size_t number_of_events = 0;

AliEventGroup *_ali_event_create_group(const char *event_name)
{
    AliEventGroup *group;

    // Too many events. :(
    if (number_of_events > ALI_EVENT_MAX_EVENT_GROUPS) {
        return NULL;
    }

    group = &(event_groups[number_of_events]);

    group->name = event_name;
    number_of_events++;

    return group;
}

AliEventGroup *_ali_event_find_or_create_group(const char *event_name)
{
    for (size_t i = 0; i < number_of_events; i++){
        AliEventGroup *group = &(event_groups[i]);

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

bool event_trigger(const char *event_name, void *data)
{
    AliEventGroup *group = _ali_event_find_or_create_group(event_name);

    // If no group is found, return false.
    if (group == NULL) {
        return false;
    }

    for (size_t i = 0; i < group->number_of_handlers; i++) {
        group->handlers[i](data);
    }

    return true;
}
