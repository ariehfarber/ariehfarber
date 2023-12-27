/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Itay Ziv	
*Date: 26/12/2023
*******************************************************************************/
#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*labs  */

#include "vsa.h"

#define WORD_SIZE sizeof(size_t)
#define END_OF_POOL 0
#define MIN_POOL_SIZE ((2 * sizeof(vsa_t)) + WORD_SIZE)
#define VSA_OFFSET 1
#define MAGIC_NUMBER 0XBADCAFFE
 
struct vsa 
{
	long block_size;
	#ifndef NDEBUG
	long magic_number;
	#endif
};

static size_t AlignUpToWord(size_t n);
static size_t AlignDownToWord(size_t n);
static vsa_t *NextVsa(vsa_t *vsa);
static void Defrag(vsa_t *vsa);
#ifndef NDEBUG
static void AssignMagicNumber(vsa_t *vsa);
#endif

vsa_t *VSAInit(void *pool, size_t pool_size)
{
	vsa_t *vsa = pool;
	vsa_t *end_of_vsa = NULL;
	
	assert(NULL != pool);
	assert(0 == ((size_t)pool & (WORD_SIZE - 1)));
	
	if (pool_size < MIN_POOL_SIZE)
	{
		return (NULL);
	}
	
	pool_size = AlignDownToWord(pool_size) - sizeof(vsa_t);

	vsa->block_size = (long)(pool_size - sizeof(vsa_t));
	
	end_of_vsa = (vsa_t *)((char *)vsa + pool_size);
	end_of_vsa->block_size = END_OF_POOL;

	#ifndef NDEBUG
	AssignMagicNumber(vsa);
	AssignMagicNumber(end_of_vsa);
	#endif
	
	return (vsa);
}

void *VSAAlloc(vsa_t *vsa, size_t size_to_alloc)
{
	vsa_t *vsa_runner = vsa;
	vsa_t *place_holder_vsa = NULL;
	long diff = 0;
	
	assert(NULL != vsa);
	assert(vsa->magic_number == MAGIC_NUMBER);
	
	if (0 == size_to_alloc)
	{
		return (NULL);
	}
	
	size_to_alloc = AlignUpToWord(size_to_alloc);
	
	Defrag(vsa);
	
	while (vsa_runner->block_size < (long)size_to_alloc &&\
		   END_OF_POOL != vsa_runner->block_size)
	{
		vsa_runner = NextVsa(vsa_runner);
		Defrag(vsa_runner);
	}
	
	if (END_OF_POOL == vsa_runner->block_size)
	{
		return (NULL);
	}
	
	place_holder_vsa = vsa_runner;
	
	if (vsa_runner->block_size > (long)(size_to_alloc + sizeof(vsa_t)))
	{
		diff = vsa_runner->block_size - (long)(size_to_alloc + sizeof(vsa_t));
		vsa_runner->block_size = -size_to_alloc;

		vsa_runner = NextVsa(vsa_runner);
		vsa_runner->block_size = diff;
		#ifndef NDEBUG
		AssignMagicNumber(vsa_runner);
		#endif
	}
	else
	{
		vsa_runner->block_size = -vsa_runner->block_size;
	}

	return ((void *)(place_holder_vsa + VSA_OFFSET));
}

void VSAFree(void *to_free)
{
	vsa_t *free_vsa = NULL;
	
	if (NULL == to_free)
	{
		return;
	}

	free_vsa = (vsa_t *)((vsa_t *)to_free - VSA_OFFSET);
	assert(free_vsa->magic_number == MAGIC_NUMBER);
	
	free_vsa->block_size = labs(free_vsa->block_size);
}

size_t VSALargestBlockAvailable(vsa_t *vsa)
{
	long largest_block = 0;
	
	assert(NULL != vsa);
	assert(vsa->magic_number == MAGIC_NUMBER);
	
	while (END_OF_POOL != vsa->block_size)
	{
		Defrag(vsa);
		
		if (largest_block < vsa->block_size)
		{
			largest_block = vsa->block_size;
		}	
		
		vsa = NextVsa(vsa);
	}
	
	return ((size_t)largest_block);
}

static size_t AlignUpToWord(size_t n)
{
	return ((n + (WORD_SIZE - 1)) &~ (WORD_SIZE - 1));
}

static size_t AlignDownToWord(size_t n)
{
	return (n &~ (WORD_SIZE - 1));
}

static vsa_t *NextVsa(vsa_t *vsa)
{
	return ((vsa_t *)((char *)vsa + sizeof(vsa_t) + labs(vsa->block_size)));
}

static void Defrag(vsa_t *vsa)
{
	vsa_t *vsa_runner = vsa;
	long combined_blocks = vsa->block_size;
	
	assert(NULL != vsa);
	
	if (0 >= vsa->block_size)
	{
		return;
	}
	
	vsa_runner = NextVsa(vsa_runner);
	
	while (0 < vsa_runner->block_size)
	{
		combined_blocks += vsa_runner->block_size + sizeof(vsa_t);
		vsa_runner = NextVsa(vsa_runner);
	}
	
	vsa->block_size = combined_blocks;
}

#ifndef NDEBUG
static void AssignMagicNumber(vsa_t *vsa)
{
	assert(NULL != vsa);
	
	vsa->magic_number = MAGIC_NUMBER;
}
#endif
