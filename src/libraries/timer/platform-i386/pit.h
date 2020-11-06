#ifndef AWOO_TIMER_PIT_H
#define AWOO_TIMER_PIT_H

/*
 * The PIT runs at 1.193182MHz, which is 0.83809511038551 microseconds
 * per tick.
 *
 * pit_phase(hz) will take hz, determine the divisor that causes the PIT
 * to generate (roughly) that frequency, and then set the divisor to that.
 *
 *
 * A frequency of 40kHz will give interrupts every 25 microseconds.
 * 1kHz will give interrupts every 1000 microseconds (1ms).
 */

#define PIT_FREQUENCY 40000 // 40kHz.
#define PIT_INTERVAL  25    // 25 microseconds.

#endif
