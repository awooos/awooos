#ifndef KERNEL_H
#define KERNEL_H

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <awoo/modifiers.h>
#include <eventually.h>
#include <string.h>

void hal_init();

void hal_register_events();
void tests_register_events();
void greeter_register_events();

void hal_shutdown();
void hal_hard_shutdown();
void hal_test_shutdown(bool success);

void kprint(const char *string);

noreturn _panic(const char *message, const char *function,
                const char* filename, size_t line, bool automated);

#define panic(message) _panic(message, __FUNCTION__, __FILE__, __LINE__, false)

#endif
