#include <dmm.h>
#include "paging.h"

PageDirEntry *cur_page_directory;

/* clear_page_directory(page_directory)
 * Clears the page directory given.
 */
void clear_page_directory(PageDirEntry* page_directory)
{
    unsigned int i;
    for (i = 0; i < 1024; i++) {
        page_directory[i].present = 0;
        page_directory[i].readwrite = 1;
        page_directory[i].user = 0;
    }
}

/* idmap_page_table(page_table, address)
 * Identity maps the page table given to address.
 */
void idmap_page_table(PageTableEntry* page_table, unsigned int address)
{
    unsigned int i;
    for (i = 0; i < 1024; i++, address += 0x1000) {
        page_table[i].address = address >> 12;
        page_table[i].present = 1;
        page_table[i].readwrite = 1;
        page_table[i].user = 0;
    }
}

void dmm_paging_init()
{
    PageTableEntry* page_table;

    // Create page directory
    cur_page_directory = (PageDirEntry*) kmalloc_int(sizeof(PageDirEntry)*1024, MALLOC_ALIGN);
    clear_page_directory(cur_page_directory);

    // Create a page table.
    page_table = (PageTableEntry*) kmalloc_int(sizeof(PageTableEntry)*1024, MALLOC_ALIGN);
    idmap_page_table(page_table, 0);

    // Add that page table to the page directory.
    cur_page_directory[0].address = (unsigned int) page_table >> 12;
    cur_page_directory[0].present = 1;
    cur_page_directory[0].readwrite = 1;
    cur_page_directory[0].user = 0;

    // Enable paging.
    __asm__ volatile("mov %0, %%cr3":: "b"(cur_page_directory));
    unsigned int cr0;
    __asm__ volatile("mov %%cr0, %0": "=b"(cr0));
    cr0 |= 0x80000000;
    __asm__ volatile("mov %0, %%cr0":: "b"(cr0));
}
