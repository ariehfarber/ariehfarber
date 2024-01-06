/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Yael Argov
*Date: 11/12/2023
*******************************************************************************/
#include <stddef.h> /*size_t	  */
#include <stdlib.h> /*malloc, free*/  
#include <assert.h> /*assert 	  */ 	

#include "cbuffer.h"
#include "ds_utils.h" /*TRUE*/

#define MIN(a, b) (((a) > (b)) ? (b) : (a))

#define OFFSET 1

struct buffer
{
	size_t read;
	size_t write;
	size_t capacity;
	char array[1];
};

buffer_t *BufferCreate(size_t capacity)
{
	buffer_t *buffer = NULL;
	
	buffer = (buffer_t *)malloc(sizeof(buffer_t) + (capacity * sizeof(char)));  
	if (NULL == buffer)
	{
		return NULL;
	}
	
	buffer->read = 0;
	buffer->write = 0;
	buffer->capacity = capacity;
	
	return (buffer);
}

void BufferDestroy(buffer_t *buffer)
{
	free(buffer);
}

size_t BufferRead(void *dest, buffer_t *buffer, size_t n)
{
    size_t read_elements = 0;	
    char *dest_ptr = NULL;
	
	assert(NULL != dest);
	assert(NULL != buffer);

	n = MIN(n, BufferSize(buffer));
	read_elements = n;
	dest_ptr = (char *)dest;

	while (0 != n)
	{
		*dest_ptr = buffer->array[buffer->read + OFFSET];
		++dest_ptr;
		buffer->read = (buffer->read + OFFSET) % (buffer->capacity + OFFSET);
		--n;		
	}
		
	return (read_elements);
}

size_t BufferWrite(const void *src, buffer_t *buffer, size_t n)
{
    size_t write_elements = 0;	
    char *src_ptr = NULL;
    
	assert(NULL != src);
	assert(NULL != buffer);

	n = MIN(n, BufferFreeSpace(buffer));
	write_elements = n;
	src_ptr = (char *)src;

	while (0 != n)
	{
		buffer->array[buffer->write + OFFSET] = *src_ptr;
		++src_ptr;
		buffer->write = (buffer->write + 1) % (buffer->capacity + OFFSET);
		--n;	
	}
		
	return (write_elements);
}
	
size_t BufferSize(const buffer_t *buffer)
{
	size_t array_size = 0;
	size_t write = buffer->write;
	size_t read = buffer->read;
	size_t capacity = buffer->capacity; 
	
	array_size = ((write + capacity + OFFSET) - read) % (capacity + OFFSET);
	
	return (array_size);
}

int BufferIsEmpty(const buffer_t *buffer)
{
	return (0 == BufferSize(buffer));
}

size_t BufferFreeSpace(const buffer_t* buffer)
{
	return (buffer->capacity - BufferSize(buffer));
}
