/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Ben Cohen
*Date: 27/11/2023
*******************************************************************************/
#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/

#include "ws10.h"

void *MemSet(void *str, int c, size_t n)
{
    char *runner = NULL;
    char c_character = (char)c;
    size_t word_chunk = 0;
    const size_t word_size = sizeof(size_t);
    size_t i = 0;

    assert(NULL != str);
    
    runner = (char *)str;

    for (i = 0; i < word_size; ++i) 
    {
        word_chunk <<= 8;
        word_chunk |= c_character;
    }
    
	while (0 != ((size_t)runner & (word_size - 1)) && 0 != n)
	{
		*runner = c_character;
		++runner;
		--n;
	}
  
	while (n > word_size)
	{
		*(size_t *)runner = word_chunk;
		runner += word_size;
		n -= word_size;
	}
    
    while (0 != n)
	{
		*runner = c_character;
		++runner;
		--n;
	}

    return (str);
}

void *MemCpy(void *dest, const void *src, size_t n)
{ 
    char *src_runner = NULL;
    char *dest_runner = NULL;
    size_t *aligned_src_runner = NULL;
    size_t *aligned_dest_runner = NULL;
    const size_t word_size = sizeof(size_t);
    int ptr_step = 1;

    assert(src);
	assert(dest);
	
    src_runner = (char *)src;
    dest_runner = (char *)dest;
    
	while (0 != ((size_t)src_runner & (word_size - 1)) && 0 != n)
	{
		*dest_runner = *src_runner;
		src_runner += ptr_step;
		dest_runner += ptr_step;
		--n;
	}

    aligned_src_runner = (size_t *)src_runner;
    aligned_dest_runner = (size_t *)dest_runner;
	while (n > word_size)
	{
		*aligned_dest_runner = *aligned_src_runner;
		aligned_src_runner += ptr_step;
		aligned_dest_runner += ptr_step;
		n -= word_size;
	}
   
    src_runner = (char *)aligned_src_runner;
    dest_runner = (char *)aligned_dest_runner; 
    while (0 != n)
	{
		*dest_runner = *src_runner;
		src_runner += ptr_step;
		dest_runner += ptr_step;
		--n;
	}

    return (dest); 
}

void *MemMove(void *dest, const void *src, size_t n)
{ 
    char *dest_runner = NULL;
    char *src_runner = NULL;
    size_t *aligned_dest_runner = NULL;
    size_t *aligned_src_runner = NULL;
    const size_t word_size = sizeof(size_t);
    int ptr_step = 1;

    assert(dest);
	assert(src);
	
    dest_runner = (char *)dest;
    src_runner = (char *)src;
    
    if (src < dest)
    {
    	ptr_step = -1;
	    dest_runner = (char *)dest + n - 1;
		src_runner = (char *)src + n - 1;
    }
    
	while (0 != ((size_t)dest_runner & (word_size - 1)) && 0 != n)
	{
		*dest_runner = *src_runner;
		dest_runner += ptr_step;
		src_runner += ptr_step;
		--n;
	}

	aligned_dest_runner = (size_t *)dest_runner;
	aligned_src_runner = (size_t *)src_runner;
	while (n > word_size)
	{
		*aligned_dest_runner = *aligned_src_runner;
		aligned_dest_runner += ptr_step;
		aligned_src_runner += ptr_step;
		n -= word_size;
	}
  
	dest_runner = (char *)aligned_dest_runner;
	src_runner = (char *)aligned_src_runner; 
	while (0 != n)
	{
		*dest_runner = *src_runner;
		dest_runner += ptr_step;
		src_runner += ptr_step;
		--n;
	}

    return (dest); 
}
