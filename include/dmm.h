#ifndef DUX_DMM_H
#define DUX_DMM_H

void dmm_init(unsigned int *_end_memory);
void *kmalloc(unsigned int nbytes);
void kfree(void *ap);

#endif
