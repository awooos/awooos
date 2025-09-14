void hal_interrupts_enable(void) {
    __asm__ volatile ("sti");
}

void hal_interrupts_disable(void) {
    __asm__ volatile ("cli");
}
