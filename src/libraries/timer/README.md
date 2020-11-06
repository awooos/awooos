# AwooOS - Timer library

AwooOS timer library serves two purposes:

1. It provides generic timer functionality that is independent of any timekeeping device.
2. It provides a global timer instance which is tied the platform-specific timekeeping device.

## Generic Timer

```c
int main() {
    Timer timer = {0};

    timer_increment_ms(&timer, 1000);
    timer_increment_us(&timer, 5);
    // {.seconds = 1, .microseconds = 5}
}
```

## Global Timer

```c
Timer start = {0, 0};
Timer end = {0, 0};

gtimer_copy(&start);
slow_function();
gtimer_copy(&end);

// The number of milliseconds slow_function() took to run.
TimerDuration duration = timer_duration(&start, &end);

// The number of microseconds slow_function() took to run.
TimerDuration duration_us = timer_duration_us(&start, &end);
```

## Thanks

This library took a lot of inspiration from [how polymorphOS does timers](https://gitlab.com/alxce/polymorphos/-/blob/main/src/timer.rs). ♥
