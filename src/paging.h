#ifndef DMM_PAGING_H
#define DMM_PAGING_H

#include "placement_allocator.h"
#include <stddef.h>

typedef struct {
	size_t present : 1;
	size_t readwrite : 1;
	size_t user : 1;
	size_t writethrough : 1;
	size_t cachedisable : 1;
	size_t accessed : 1;
	size_t dirty : 1;
	size_t attributeindex : 1;
	size_t global : 1;
	size_t reserved : 3;
	size_t address : 20;
} PageTableEntry;

typedef struct {
	size_t present : 1;
	size_t readwrite : 1;
	size_t user : 1;
	size_t writethrough : 1;
	size_t cachedisable : 1;
	size_t accessed : 1;
	size_t available : 1;
	size_t pagesize : 1;
	size_t global : 1;
	size_t reserved : 3;
	size_t address : 20;
} PageDirEntry;

void clear_page_directory(PageDirEntry* page_directory);
void idmap_page_table(PageTableEntry* page_table, size_t address);
void dmm_paging_init();

#endif
