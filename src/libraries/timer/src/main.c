#include <timer.h>
#include <stddef.h>
#include <string.h>

#define US_IN_1S 1000000

/// Increment +timer+ by the specified number of microseconds.
void timer_increment_us(Timer *timer, uint32_t microseconds) {
    timer->microseconds += microseconds;
    while (timer->microseconds > US_IN_1S) {
        timer->microseconds -= US_IN_1S;
        timer->seconds += 1;
    }
}

/// Increment +timer+ by the specified number of milliseconds.
void timer_increment_ms(Timer *timer, uint32_t milliseconds) {
    timer_increment_us(timer, milliseconds * 1000);
}

/// Return the duration stored in +timer+, converted to microseconds.
TimerDuration timer_in_microseconds(Timer *timer) {
    return (timer->seconds * US_IN_1S) + (TimerDuration)timer->microseconds;
}

/// Return the duration stored in +timer+, converted to milliseconds.
TimerDuration timer_in_milliseconds(Timer *timer) {
    return (timer->seconds * 1000) + (uint64_t)(timer->microseconds / 1000);
}

TimerDuration timer_duration_us(Timer *start, Timer *end) {
    return timer_in_microseconds(end) - timer_in_microseconds(start);
}

TimerDuration timer_duration(Timer *start, Timer *end) {
    return timer_in_milliseconds(end) - timer_in_milliseconds(start);
}

/// Copy the duration stored in +original+ to +copy+.
/// NOTE: Any information in +copy+ will be lost.
void timer_copy(Timer *original, Timer *copy) {
    // memcpy is used, instead of just assignments, because
    // pointers to uint64_t result in invalid opcodes.
    memcpy(copy, original, sizeof(Timer));
}

#undef US_IN_1S
