#include <kernel.h>
#include <awoostr.h>
#include "idt.h"
#include "exceptions.h"
#include "ports.h"
#include <eventually.h>
#include <string.h>
#include <stdlib.h>

static const char *exceptions[32] = {
    "0 #DE Divide Error",
    "1 #DB RESERVED",
    "2 - NMI Interrupt",
    "3 #BP Breakpoint",
    "4 #OF Overflow",
    "5 #BR BOUND Range Exceeded",
    "6 #UD Invalid Opcode (Undefined Opcode)",
    "7 #NM Device Not Available (No Math Coprocessor)",
    "8 #DF Double Fault",
    "9   Coprocessor Segment Overrun (reserved)",
    "10 #TS Invalid TSS",
    "11 #NP Segment Not Present",
    "12 #SS Stack-Segment Fault",
    "13 #GP General Protection",
    "14 #PF Page Fault",
    "15 - (Intel reserved. Do not use.)",
    "16 #MF x87 FPU Floating-Point Error (Math Fault)",
    "17 #AC Alignment Check",
    "18 #MC Machine Check",
    "19 #XM SIMD Floating-Point Exception",
    "20 - Intel reserved. Do not use.",
    "21 - Intel reserved. Do not use.",
    "22 - Intel reserved. Do not use.",
    "23 - Intel reserved. Do not use.",
    "24 - Intel reserved. Do not use.",
    "25 - Intel reserved. Do not use.",
    "26 - Intel reserved. Do not use.",
    "27 - Intel reserved. Do not use.",
    "28 - Intel reserved. Do not use.",
    "29 - Intel reserved. Do not use.",
    "30 - Intel reserved. Do not use.",
    "31 - Intel reserved. Do not use."
};

// https://en.wikipedia.org/wiki/Interrupt_request_%28PC_architecture%29#x86_IRQs
static const char *irq_names[16] = {
    // PIC 1.
    "IRQ 0 timer",
    "IRQ 1 keyboard",
    "IRQ 2", // Cascaded signals from IRQs 8-15 on the second PIC.
    "IRQ 3 serial 1",
    "IRQ 4 serial 2",
    "IRQ 5 parallel 2/3",
    "IRQ 6 floppy controller",
    "IRQ 7 parallel 1"

    // PIC 2.
    "IRQ 8 real-time clock",
    "IRQ 9 ACPI",
    "IRQ 10", // For peripherals.
    "IRQ 11", // For peripherals.
    "IRQ 12", // PS/2 mouse.
    "IRQ 13", // Co-processor, FPU, or inter-processor interrupt.
    "IRQ 14 ATA",
    "IRQ 15 ATA",
};

void hal_exception_handler(Registers *r)
{
    Registers *r2 = malloc(sizeof(r));
    memcpy(r2, r, sizeof(Registers));

    /*if (r->int_no == SYSCALL_INTERRUPT) {
        HalSyscallHandler(r);
    } else if(r->int_no == 3) {
        // call a debugger.
    } else*/ if(r->int_no < 32){
        panic((char*)exceptions[r->int_no]);
    } else {
        eventually_event_trigger(irq_names[r->int_no - 32], r2);
    }

    // Interrupts 32+ are IRQs, so we need to send EOIs.
    if (r->int_no > 31) {
        /* We need to send an EOI to the
         *  interrupt controllers too */

        // If it's involved, send an EOI to the "slave" controller.
        // (It's involved for IRQs 9 and up.
        if (r->int_no > (31 + 8)) {
            hal_outb(0xA0, 0x20);
        }

        hal_outb(0x20, 0x20);
    }
}

void hal_irq_remap()
{
    // Starts the initialization sequence.
    hal_outb(PIC1_COMMAND, ICW1_INIT + ICW1_ICW4);
    hal_outb(PIC2_COMMAND, ICW1_INIT + ICW1_ICW4);

    // Define the PIC vectors.
    hal_outb(PIC1_DATA, 0x20);
    hal_outb(PIC2_DATA, 0x28);

    // Continue initialization sequence.
    hal_outb(PIC1_DATA, 4);
    hal_outb(PIC2_DATA, 2);

    hal_outb(PIC1_DATA, ICW4_8086);
    hal_outb(PIC2_DATA, ICW4_8086);

    // Unmask all interrupts on PIC1.
    hal_outb(PIC1_DATA, 0x0);

    // Unmask all interrupts on PIC2.
    hal_outb(PIC2_DATA, 0x0);
}

#define EXCEPTION(n) extern void hal_exception_##n(); \
    hal_idt_register_exception(n, (size_t)hal_exception_##n);

void hal_exceptions_init()
{
    hal_irq_remap();

    EXCEPTION(0);
    EXCEPTION(1);
    EXCEPTION(2);
    EXCEPTION(3);
    EXCEPTION(4);
    EXCEPTION(5);
    EXCEPTION(6);
    EXCEPTION(7);
    EXCEPTION(8);
    EXCEPTION(9);
    EXCEPTION(10);
    EXCEPTION(11);
    EXCEPTION(12);
    EXCEPTION(13);
    EXCEPTION(14);
    EXCEPTION(15);
    EXCEPTION(16);
    EXCEPTION(17);
    EXCEPTION(18);
    EXCEPTION(19);
    EXCEPTION(20);
    EXCEPTION(21);
    EXCEPTION(22);
    EXCEPTION(23);
    EXCEPTION(24);
    EXCEPTION(25);
    EXCEPTION(26);
    EXCEPTION(27);
    EXCEPTION(28);
    EXCEPTION(29);
    EXCEPTION(30);
    EXCEPTION(31);
    EXCEPTION(32);
    EXCEPTION(33);
    EXCEPTION(34);
    EXCEPTION(35);
    EXCEPTION(36);
    EXCEPTION(37);
    EXCEPTION(38);
    EXCEPTION(39);
    EXCEPTION(40);
    EXCEPTION(41);
    EXCEPTION(42);
    EXCEPTION(43);
    EXCEPTION(44);
    EXCEPTION(45);
    EXCEPTION(46);
    EXCEPTION(47);
}
