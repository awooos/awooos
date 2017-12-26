#include <kernel.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <scheduler.h>
#include <eventually.h>

// NOTE: This scheduler is implemented so that it does not need malloc().
//       Mostly because I'm too lazy to implement a good allocator. —@duckinator

// WARNING: I highly doubt this will work at all with multiple cores enabled.

SchedulerState state;

size_t current_process = 0;
size_t number_of_processes = 0;

void scheduler_init()
{
    memset(&state, 0, sizeof(SchedulerState));
}

// Compacts the array of processes, so there are no empty chunks.
//
// ASSUMPTION: There will never be multiple adjacent unused processes.
// NOTE: This can probably be optimized a shitton. Or removed entirely.
void scheduler_reflow_processes()
{
    Process *current;
    Process *next;
    Process tmp;

    for (size_t i = 0; i < number_of_processes; i++) {
        current = &state.processes[i];
        next = &state.processes[i + 1];

        if (current->used == 0) {
            memcpy((void*)current, (void*)next, sizeof(Process));
            // the following memset() implicitly sets next->used to zero.
            memset((void*)next, 0, sizeof(Process));
        }
    }
}

MAY_PANIC void scheduler_process_start(const char *event_name, void *data)
{
    size_t pid;

    // Don't start a new process if we don't have enough space!
    if ((state.number_of_processes + 1) >= MAX_PROCESSES) {
        return;
    }

    pid = state.number_of_processes;
    state.number_of_processes += 1;

    return;
}

MAY_PANIC void scheduler_process_stop(const char *event_name, void *data)
{
    ProcessReference *process_reference = (ProcessReference*)data;
    size_t pid = process_reference->id;
    Process *proc = &state.processes[pid];

    if (eventually_event_trigger("HAL scheduler destroy process", &state)) {
        memset(proc, 0, sizeof(Process));
    } else {
        // TODO: implement format().
        panic(/*format(*/"Unable to destroy process! {}"/*, pid)*/);
    }

    scheduler_reflow_processes();
    number_of_processes -= 1;
}

MAY_PANIC void scheduler_process_next(const char *event_name, void *data)
{
    state.processes[current_process].data = data;
    eventually_event_trigger("HAL scheduler next", &state);
}
