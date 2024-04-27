# Dynamic-Storage-Allocation

Did a First Fit allocation:
Allocated the first block on the list that is big enough to satisfy a request

Created two different functions, my_malloc() and my_free() that mimicks the malloc() and free() functions in C, which trying to maximize efficiency while minimizing any fragmentation.

My implementation involves a static memory array that has a global definition on its maximum size. In my my_malloc.h file, I have used a list data structure where each “node” represents a block of memory. In each block of memory, it contains the size of memory inside the block while it also stores the pointer to its adjacent blocks, which are declared as ‘prev’ and ‘next’. With that, when I initialize the memory, it creates a free list with exactly one block. As that is a new memory of one block, it would not have any adjacent blocks of memory, therefore their ‘prev’ and ‘next’ pointers are set to NULL. Additionally, as it is a newly allocated memory, it is not used by anything yet, and therefore it’s block of memory is set to be ‘free’.

# my_malloc() function:

started traversing from the very first block in the list to find a free block of memory that is large enough to store a data. This takes O(N) time since it starts traversing from the first block. 

# my_free() function:

That was where the having a doubly-linked list comes in handy. Firstly, I checked if the pointer argument that is attempted to be freed is within the range of the start of the first block of memory and the end of the very last block. If it’s not, it is not a valid pointer, which returns an error message. Else, we free that block of memory, and set the pointer to be at the start of that block so that it can allocate memory in that area again. At the same time, this is when I said earlier that doubly linked list allows a constant time ‘free’. This is because up till now, operation has been executed in constant time. The next part was trying to merge any potential contiguous free blocks of memory now that the block of memory at ‘ptr’ is now free. In my static function “coalesce”, instead of having to traverse through the entire list which would once again take O(N), I can just take the current block and compare it with its adjacent blocks (‘prev’ and ‘next’) to see if any (or both) of them are also free. If any (or all) of them are free, then I would be able to merge them into one contiguous block. Therefore, each lookup only takes a constant time lookup, including the merging.