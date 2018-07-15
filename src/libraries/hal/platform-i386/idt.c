#include <ali/event.h>
#include <stdint.h>
#include "idt.h"

IdtPointer idtd;
IdtEntry idt[256] = {{0,0,0,0,0}};

void hal_idt_load()
{
    __asm__ __volatile__ ("lidt %0" : : "m" (idtd));
}

void hal_idt_init()
{
    idtd.offset = (uint32_t)idt;
    idtd.size = sizeof(IdtEntry) * 256 - 1;

    hal_idt_load();
}

__attribute__((constructor))
void hal_idt_register_events()
{
    event_watch("HAL init", &hal_idt_init);
}


void hal_idt_set_gate(size_t n, uint32_t offset, uint16_t selector,
        uint8_t priv, uint8_t sys, uint8_t gatetype)
{
    idt[n].offset_lo = offset & 0xffff;
    idt[n].selector = selector;
    idt[n].zero = 0;
    idt[n].type = (uint8_t)(0x80 | (priv << 5 & 0x3) | (sys << 4 & 0x1) | (gatetype & 0xf));
    idt[n].offset_hi = (uint16_t)(offset >> 16 & 0xffff);
}

void hal_idt_register_exception(size_t n, uint32_t offset)
{
    hal_idt_set_gate(n, (size_t)offset, 0x8, 0, 0, IDT_INTR32);
}
