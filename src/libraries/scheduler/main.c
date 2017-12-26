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
    memset(state.processes, 0, sizeof(Process) * MAX_PROCESSES);
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

MAY_PANIC void scheduler_destroy_process(size_t pid)
{
    Process *proc = &state.processes[pid];

    memset(proc, 0, sizeof(Process));

    if (proc->used != 0) {
        // TODO: implement format().
        panic(/*format(*/"Unable to destroy process! {}"/*, pid)*/);
    }

    scheduler_reflow_processes();
    number_of_processes -= 1;
}

bool scheduler_start_process()
{
    size_t pid;

    // Don't start a new process if we don't have enough space!
    if ((state.number_of_processes + 1) >= MAX_PROCESSES) {
        return false;
    }

    pid = state.number_of_processes;
    state.number_of_processes += 1;

    return true;
}

MAY_PANIC void scheduler_callback(UNUSED char *event_name, UNUSED void *data)
{
    eventually_event_trigger("HAL scheduler next", &state);
}
