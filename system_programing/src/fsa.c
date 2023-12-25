/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/

#include "fsa.h"

#define WORD_SIZE sizeof(size_t)
#define ZERO 0

struct fsa
{
	size_t next_available;
};

size_t FSASuggestSize(size_t num_of_blocks, size_t block_size)
{
	size_t suggested_size = 0;
	
	block_size += (WORD_SIZE - block_size % WORD_SIZE) % WORD_SIZE;
	
	suggested_size = (block_size * num_of_blocks) + sizeof(fsa_t);
	
	return (suggested_size);
}

fsa_t *FSAInit(void *pool, size_t block_size, size_t pool_size)
{
	fsa_t *fsa = NULL;
	char *runner = NULL;
	size_t i = 0;
	
	assert (NULL != pool);
	
	fsa = pool;
	fsa->next_available = sizeof(fsa_t);
	runner = (char *)fsa + fsa->next_available;
	
	for (i = fsa->next_available; i < (pool_size - block_size); i += block_size)
	{
		*(size_t *)runner = i + block_size;
		runner += block_size;
	}
	*(size_t *)runner = 0;
	
	return (fsa);
}

void *FSAAlloc(fsa_t *fsa)
{
	char *block_pointer = NULL;
	
	assert (NULL != fsa);
	
	if (ZERO == fsa->next_available)
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
	
	*(size_t *)to_free = fsa->next_available;
	fsa->next_available = (char *)to_free - (char *)fsa;
}

size_t FSACountFree(fsa_t *fsa)
{
	size_t temp = 0;
	size_t counter = 0;
	
	temp = fsa->next_available;
	
	while (ZERO != temp)
	{
		++counter;
		temp = *(size_t *)((char *)fsa + temp);

	}
	
	return (counter);
}
