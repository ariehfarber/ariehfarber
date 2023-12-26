/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Michal Fingerut & Gidron Bloch
*Date: 25/12/2023
*******************************************************************************/
#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/

#include "fsa.h"

#define WORD_SIZE sizeof(size_t)
#define END_OF_POOL 0

struct fsa
{
	size_t next_available;
};

static size_t AlignUpToWord(size_t n);

size_t FSASuggestSize(size_t num_of_blocks, size_t block_size)
{
	return ((AlignUpToWord(block_size) * num_of_blocks) + sizeof(fsa_t));
}

fsa_t *FSAInit(void *pool, size_t block_size, size_t pool_size)
{
	fsa_t *fsa = pool;
	char *runner = NULL;
	size_t i = 0;
	
	assert (NULL != pool);
	assert (0 == pool_size % WORD_SIZE);
	
	fsa->next_available = sizeof(fsa_t);
	runner = (char *)fsa + fsa->next_available;
	block_size = AlignUpToWord(block_size);
	
	for (i = fsa->next_available; i < (pool_size - block_size); i += block_size)
	{
		*(size_t *)runner = i + block_size;
		runner += block_size;
	}
	*(size_t *)runner = END_OF_POOL;
	
	return (fsa);
}

void *FSAAlloc(fsa_t *fsa)
{
	char *block_pointer = NULL;
	
	assert (NULL != fsa);
	
	if (END_OF_POOL == fsa->next_available)
	{
		return (NULL);
	}
	
	block_pointer = (char *)fsa + fsa->next_available;
	fsa->next_available = *(size_t *)block_pointer;
	
	return ((void *)block_pointer);
}

void FSAFree(fsa_t *fsa, void *to_free)
{
	assert (NULL != fsa);
	assert (NULL != to_free);
	
	*(size_t *)to_free = fsa->next_available;
	fsa->next_available = (char *)to_free - (char *)fsa;
}

size_t FSACountFree(fsa_t *fsa)
{
	size_t runner = fsa->next_available;
	size_t counter = 0;
	
	while (END_OF_POOL != runner)
	{
		++counter;
		runner = *(size_t *)((char *)fsa + runner);
	}
	
	return (counter);
}

static size_t AlignUpToWord(size_t n)
{
	return ((n + (WORD_SIZE - 1)) &~ (WORD_SIZE - 1));
}
