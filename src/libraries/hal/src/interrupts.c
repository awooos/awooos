#include "interrupts.h"

void hal_enable_interrupts()
{
    __asm__ volatile ("sti");
}

void hal_disable_interrupts()
{
    __asm__ volatile ("cli");
}

