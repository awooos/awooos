#ifndef IRQ_H
#define IRQ_H

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
    "IRQ 7 parallel 1",

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

#endif
