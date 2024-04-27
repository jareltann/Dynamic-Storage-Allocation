#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "my_malloc.h"

int main() {
    // Initialize memory
    mem_init();


    // Test Case 1: Allocate and Free a Small Block
    int* smallBlock = (int*)my_malloc(10 * sizeof(int));


  if (smallBlock != NULL) {
        printf("Block Address: %p\n", smallBlock);
        my_free(smallBlock);
    } else {
        printf("Memory allocation failed for the small block\n");
    }

    // Test Case 2: Allocate and Free a Large Block
    char* largeBlock = (char*)my_malloc(500);
    if (largeBlock != NULL) {
        printf("Block Address: %p\n", largeBlock);
        my_free(largeBlock);
    } else {
        printf("Memory allocation failed for the large block\n");
    }

    // Test Case 3: Allocate Multiple Blocks and Free Them
    int* block1 = (int*)my_malloc(50 * sizeof(int));
    char* block2 = (char*)my_malloc(200);
    int* block3 = (int*)my_malloc(100 * sizeof(int));

    if (block1 != NULL && block2 != NULL && block3 != NULL) {

        // Print addresses for clarity
        printf("Block 1 Address: %p\n", block1);
        printf("Block 2 Address: %p\n", block2);
        printf("Block 3 Address: %p\n", block3);

        my_free(block1);
        my_free(block2);
        my_free(block3);

    }

    else {
        printf("Memory allocation failed for multiple blocks\n");
    }

    // Test Case 4: Attempt to Free an Invalid Pointer
    int invalidPointer = 42;
    my_free(&invalidPointer); // should return an error message since it's not a valid pointer

    // Test Case 5: Allocate More Than Available Memory
    int* tooLargeBlock = (int*)my_malloc(MEM_SIZE + 1);

    // should return the following error message
    if (tooLargeBlock == NULL) {
        printf("Attempted to allocate more memory than available. Allocation failed (as expected).\n");
    }


    return 0;
}




















