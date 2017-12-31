#ifndef KERNEL_H
#define KERNEL_H

#include <stddef.h>
#include <stdbool.h>
#include <awoo/modifiers.h>

void hal_init();
void hal_enable_interrupts();
void hal_disable_interrupts();
void hal_events_init();
void hal_shutdown();
void hal_hard_shutdown();
void hal_test_shutdown(bool success);
size_t *hal_badmalloc_start_address();
char *hal_compiler_information();
void kprint(const char *string);

noreturn _panic(const char *message, const char *function,
                const char* filename, size_t line, bool automated);

#define panic(message) _panic(message, __FUNCTION__, __FILE__, __LINE__, false)

#if AWOO_BUILD_TYPE_NUMBER == AWOO_TEST_BUILD
#define test_panic(message) _panic(message, __FUNCTION__, __FILE__, __LINE__, true)
#else
#define test_panic(message) panic("test_panic() should not be called in a non-test build!")
#endif

#endif
