#ifndef HAL_SCHEDULER_H
#define HAL_SCHEDULER_H

MAY_PANIC void hal_scheduler_process_next(UNUSED const char *event_name,
        void *_state, size_t data_size);

MAY_PANIC void hal_scheduler_process_start(UNUSED const char *event_name,
        void *_state, size_t data_size);

MAY_PANIC void hal_scheduler_process_stop(UNUSED const char *event_name,
        void *_state, size_t data_size);

#endif