#ifndef HAL_IDT_H
#define HAL_IDT_H

#include <stdint.h>
#include <stddef.h>

typedef struct idt_pointer_s {
    uint16_t size;
    uint32_t offset __attribute__((packed));
} IdtPointer;

typedef struct idt_entry_s {
    uint16_t offset_lo;
    uint16_t selector;
    uint8_t zero;
    uint8_t type;
    uint16_t offset_hi;
} IdtEntry;

#define IDT_TASK 0x5
#define IDT_INTR16 0x6
#define IDT_INTR32 0xe
#define IDT_TRAP16 0x7
#define IDT_TRAP32 0xf

void hal_idt_register_exception(size_t n, uint32_t offset);

void hal_idt_init(void);

#endif
