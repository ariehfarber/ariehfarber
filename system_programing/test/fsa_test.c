/*******************************************************************************
*Author: Ben Naori 
*******************************************************************************/
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */

#include "fsa.h"

void TestFuncs(void);
void PrintFSA(fsa_t *fsa, size_t size, size_t block_size);

int main(void)
{
	TestFuncs();
	
	return (0);
}

void TestFuncs(void)
{
	size_t num_of_blocks = 5;
	size_t block_size = 8;

	size_t arr[5] = {1, 2, 3, 4, 5};
	size_t *allocs[5];
	size_t **res = NULL;

	size_t total = FSASuggestSize(num_of_blocks, block_size);

	void *pool = malloc(total);

	fsa_t *fsa = FSAInit(pool, block_size, total);

	for (res = allocs; res - allocs < 5; ++res)
	{
		*res = FSAAlloc(fsa);
		**res = arr[(res - allocs)];
	}

	printf("expected-\nnext available: 0\n1, 2, 3, 4, 5\n");
	PrintFSA(fsa, num_of_blocks, block_size);

	printf("count: %ld, expected 0\n\n", FSACountFree(fsa));

	FSAFree(fsa, (void *)allocs[4]);
	FSAFree(fsa, (void *)allocs[2]);
	FSAFree(fsa, (void *)allocs[1]);

	printf("expected-\nnext available: 16\n1, 24, 40, 4, 0\n");
	PrintFSA(fsa, num_of_blocks, block_size);

	printf("count: %ld, expected 3\n\n", FSACountFree(fsa));

	allocs[4] = FSAAlloc(fsa);
	*allocs[4] = arr[4];
	allocs[2] = FSAAlloc(fsa);
	*allocs[2] = arr[2];

	printf("expected-\nnext available: 40\n1, 5, 3, 4, 0\n");
	PrintFSA(fsa, num_of_blocks, block_size);

	printf("count: %ld, expected 1\n\n", FSACountFree(fsa));

	free(pool);
}

void PrintFSA(fsa_t *fsa, size_t size, size_t block_size)
{
	size_t *ptr = (size_t *)fsa + 1;

	(void)block_size;

	printf("value-\n");
	printf("next available: %ld\n", *(size_t *)fsa);
	for (; size > 1; --size, ++ptr)
	{
		printf("%lu, ", *ptr);
	}
	printf("%lu\n", *ptr);
}
