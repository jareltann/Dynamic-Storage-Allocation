#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "my_malloc.h"


static char memory[MEM_SIZE];


static Block* List = (void*)memory;  // Pointer to the first block in the memory


void mem_init() {

	if (List == NULL){
		fprintf(stderr, "Oh no, memory initialization failed!\n");
		exit(-1);
	}

        List->size = MEM_SIZE - sizeof(Block);
        List->free = true;
        List->next = NULL;
	List->prev = NULL;

}


void *my_malloc(size_t size){

        struct Block *current;
        void* result;

        if (List == NULL){
                mem_init();
        }

        current = List;

        while((current->size < size || current->free == false) && (current->next != NULL)){
                current = current->next;
        }

        if ((current->size) == size){
                current->free = false;
                result = (void*)(current + 1);
                return result;
        }

        else if ((current->size) > (size + sizeof(Block))){ //memory requested is not as big as the block, so split to avoid fragmentation
		struct Block* newBlock = (void*)((void*)current + size + sizeof(Block));
	        newBlock->size = current->size - size - sizeof(Block);
        	newBlock->free = true;
        	newBlock->next = current->next;
        	newBlock->prev = current;
        	current->size = size;
        	current->free = false;
        	current->next = newBlock;
                result = (void*)(current + 1);
                return result;
        }

        else{ //unable to request memory
                result = NULL;
		fprintf(stderr, "Whoops, unable to request additional memory. Too bad!\n");
                return result;
        }

}


static void coalesce(Block* current){

        if (current->next != NULL && current->next->free == true && current->prev != NULL && current->prev->free == true){
                current->size += current->prev->size + current->next->size + sizeof(Block);
                current->prev = current->prev->prev;
                current->next = current->next->next;
        }

	else if (current->prev != NULL && current->prev->free == true){
		current->size += current->prev->size + sizeof(Block);
		current->prev = current->prev->prev;
	}

	else if (current->next != NULL && current->next->free == true){
		current->size += current->next->size + sizeof(Block);
		current->next = current->next->next;
	}

}


void my_free(void *ptr){

	// check if ptr is within the legal limit to prevent illegal access
	// should be between start of first block of memory and the end

        if (((void*)memory <= ptr) && (ptr <= (void*)(memory+MEM_SIZE))){
                struct Block* current = ptr;
                current--;
                current->free = true;
                coalesce(current);
        }

        else{
                fprintf(stderr,"Your pointer is out of the range of memory allocated for you, try again :(\n");
        }

}
