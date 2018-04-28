#ifndef HAL__HAL_H
#define HAL__HAL_H

void hal_init();
void hal_register_events();

int kprint(const char *string);

void add_hal_tests();

#endif
