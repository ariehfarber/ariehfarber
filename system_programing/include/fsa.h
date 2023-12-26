/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Michal Fingerut & Gidron Bloch
*Date: 25/12/2023
*******************************************************************************/
#ifndef __FSA_H__
#define __FSA_H__

#include <stddef.h> /*size_t*/

typedef struct fsa fsa_t;

/*******************************************************************************
*Description: Suggestes a total byte size for a pool.
*Parameters: num_of_blocks - total blocks in the pool.
*			 block_size - size of a single block.
*Return Value: The minimal amount of bytes that suffices for the 
* 			   fixed size allocator pool.
*Time Complexity: O(1)
*Space Complexity: O(1)
*******************************************************************************/
size_t FSASuggestSize(size_t num_of_blocks, size_t block_size);

/*******************************************************************************
*Description: Initializes the fixed size allocator struct in the pool.
*Parameters: pool - address to an allocated memory.
* 			 block_size - size of a single block.
* 			 pool_size - total byte size of the pool.
*Return Value: Pointer to the fixed size allocator.
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: if pool_size isn't sufficient it will lead to undefined behavior. 
*		Use FSASuggestSize.
*******************************************************************************/
fsa_t *FSAInit(void *pool, size_t block_size, size_t pool_size);

/*******************************************************************************
*Description: Allocates a single block_size of memory.
*Parameters: fsa - Pointer to a fixed size allocator.
*Return Value: Pointer to the first address of a free block_size memory.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Returns NULL if no blocks are available.
*******************************************************************************/
void *FSAAlloc(fsa_t *fsa);

/*******************************************************************************
*Description: Deallocates the block pointed to by *to_free.
*Parameters: fsa - Pointer to a fixed size allocator.
*			 to_free - Pointer to an allocated block.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: If to_free wasnt allocated by FSAAlloc it will lead to 
*		undefined behavior.
*******************************************************************************/
void FSAFree(fsa_t *fsa, void *to_free);

/*******************************************************************************
*Description: Counts the available blocks in the fixed size allocator pool.
*Parameters: fsa - Pointer to a fixed size allocator.
*Return Value: The amount of blocks that are available in the pool.
*Time Complexity: O(n)
*Space Complexity: O(1)
*******************************************************************************/
size_t FSACountFree(fsa_t *fsa);

#endif /*__FSA_H__*/
