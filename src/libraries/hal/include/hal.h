#ifndef HAL__HAL_H
#define HAL__HAL_H

void hal_init(void);
void hal_print(const char *string);
void add_hal_tests(void);

void hal_interrupts_enable(void);
void hal_interrupts_disable(void);

void hal_shutdown(void);
void hal_shutdown_test_fail(void);

#endif
