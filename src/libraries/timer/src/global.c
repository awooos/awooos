#include <timer.h>

static Timer _gtimer;

/// Increment the global timer by the specified number of microseconds.
void gtimer_increment_us(uint32_t microseconds) {
    timer_increment_us(&_gtimer, microseconds);
}

/// Increment the global timer by the specified number of milliseconds.
void gtimer_increment_ms(uint32_t milliseconds) {
    timer_increment_ms(&_gtimer, milliseconds);
}

/// Return the duration stored in the global timer, converted to microseconds.
uint64_t gtimer_in_microseconds() {
    return timer_in_microseconds(&_gtimer);
}

/// Return the duration stored in the global timer, converted to milliseconds.
uint64_t gtimer_in_milliseconds() {
    return timer_in_milliseconds(&_gtimer);
}

/// Copy the duration stored in the global timer to +copy+.
/// NOTE: Any information in +copy+ will be lost.
void gtimer_copy(Timer *copy) {
    timer_copy(&_gtimer, copy);
}
