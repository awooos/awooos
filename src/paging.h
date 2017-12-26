#ifndef DMM_PAGING_H
#define DMM_PAGING_H

#include "placement_allocator.h"

typedef struct {
	unsigned int present : 1;
	unsigned int readwrite : 1;
	unsigned int user : 1;
	unsigned int writethrough : 1;
	unsigned int cachedisable : 1;
	unsigned int accessed : 1;
	unsigned int dirty : 1;
	unsigned int attributeindex : 1;
	unsigned int global : 1;
	unsigned int reserved : 3;
	unsigned int address : 20;
} PageTableEntry;

typedef struct {
	unsigned int present : 1;
	unsigned int readwrite : 1;
	unsigned int user : 1;
	unsigned int writethrough : 1;
	unsigned int cachedisable : 1;
	unsigned int accessed : 1;
	unsigned int available : 1;
	unsigned int pagesize : 1;
	unsigned int global : 1;
	unsigned int reserved : 3;
	unsigned int address : 20;
} PageDirEntry;

void clear_page_directory(PageDirEntry* page_directory);
void idmap_page_table(PageTableEntry* page_table, unsigned int address);
void dmm_paging_init();

#endif
