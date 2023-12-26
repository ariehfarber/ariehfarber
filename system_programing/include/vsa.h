/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Itay Ziv	
*Date: 26/12/2023
*******************************************************************************/
#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h> /*size_t*/

typedef struct vsa vsa_t;

/*******************************************************************************
*Description: Initializes the variable size allocator with the given pool. 
*Params: pool - Address of the allocated memory pool.
*        pool_size - Total size of the allocated memory.          
*Return Value: Address of the start of the pool.
*              If pool_size isn't large enogh returns NULL.
*Time Complexity: O(1)
*Space Complexity: O(1)
*******************************************************************************/
vsa_t *VSAInit(void *pool, size_t pool_size);

/*******************************************************************************
*Description: Allocates a block of given size.
*Params: vsa - The allocator returned by VSAInit.
*        size_to_alloc - Size of the block in bytes.
*Return Value: Pointer to the start of the alocted block. If not enough memory 
*              is available returns NULL. 
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: vsa must be init by VSAInit, otherwise it will lead to undefined 
*		behavior. 
*******************************************************************************/
void *VSAAlloc(vsa_t *vsa, size_t size_to_alloc);

/*******************************************************************************
*Description: Deallocates the block pointed by to_free.
*Params: to_free - Address of the allocted block.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: to_free must be allocted by VSAAlloc, undefined behavior otherwise.
*******************************************************************************/
void VSAFree(void *to_free);

/*******************************************************************************
*Description: Calculate the size of the largest available block in the pool.
*Params: vsa - The allocator returned by VSAInit.
*Return Value: Size of the largest available block in the pool.
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: vsa must be init by VSAInit, otherwise it will lead to undefined 
*		behavior. 
*******************************************************************************/
size_t VSALargestBlockAvailable(vsa_t *vsa);

#endif /*__VSA_H__*/
