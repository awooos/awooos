#ifndef HAL_GDT_H
#define HAL_GDT_H

void hal_gdt_init();
void hal_gdt_load_esp0_into_tss();
void hal_tss_flush();


#endif
