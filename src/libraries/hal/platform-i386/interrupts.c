#include <ali/modifiers.h>
#include "interrupts.h"

void hal_interrupts_enable(UNUSED void *data)
{
    __asm__ volatile ("sti");
}

void hal_interrupts_disable(UNUSED void *data)
{
    __asm__ volatile ("cli");
}

