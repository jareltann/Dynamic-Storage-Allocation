#ifndef _MY_MALLOC_H
#define _MY_MALLOC_H

#define MEM_SIZE 1024


typedef struct Block {
    size_t size;
    struct Block* next;
    struct Block* prev;
    bool free;
} Block;


void mem_init();
void *my_malloc(size_t size);
void my_free(void* ptr);

#endif
