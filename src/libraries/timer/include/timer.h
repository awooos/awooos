#ifndef AWOO_TIMER_H
#define AWOO_TIMER_H

#include <stdint.h>

typedef struct Timer_s {
    uint64_t seconds;
    uint32_t microseconds;
} Timer;

typedef uint64_t TimerDuration;

void timer_increment_us(Timer *timer, uint32_t microseconds);
void timer_increment_ms(Timer *timer, uint32_t milliseconds);
TimerDuration timer_in_microseconds(Timer *timer);
TimerDuration timer_in_milliseconds(Timer *timer);
TimerDuration timer_duration_us(Timer *start, Timer *end);
TimerDuration timer_duration(Timer *start, Timer *end);
void timer_copy(Timer *original, Timer *copy);

void gtimer_increment_us(uint32_t microseconds);
void gtimer_increment_ms(uint32_t milliseconds);
TimerDuration gtimer_in_microseconds(void);
TimerDuration gtimer_in_milliseconds(void);
void gtimer_copy(Timer *copy);

void add_timer_tests(void);

void timer_init(void);

#endif
