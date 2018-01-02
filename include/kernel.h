#ifndef KERNEL_H
#define KERNEL_H

#include <stdlib.h>
#include <stdbool.h>
#include <eventually.h>
#include <awoo/modifiers.h>

void hal_register_events();
void tests_register_events();
void greeter_register_events();

void hal_test_shutdown(bool success);

#define kprint(STRING) eventually_event_trigger_immediate("kernel print", (char*)STRING, 0);

noreturn _panic(const char *message, const char *function,
                const char* filename, size_t line, bool automated);

#define panic(message) _panic(message, __FUNCTION__, __FILE__, __LINE__, false)

#endif
