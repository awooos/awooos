#ifndef KERNEL_H
#define KERNEL_H

#include <stddef.h>
#include <stdbool.h>
#include <eventually.h>
#include <flail.h>
#include <awoo/modifiers.h>

void hal_register_events();
void tests_register_events();
void greeter_register_events();

int kprint(const char *string);

#define panic(message) flail_panic(message)

#endif
