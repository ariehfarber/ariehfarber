/*******************************************************************************
*Author: Arieh Farber 
*Reviewer:  
*Date: 
*******************************************************************************/
#include <stddef.h>    /*size_t, ofsetof*/
#include <stdlib.h>    /*malloc, free	*/  
#include <string.h>    /*memcpy		 	*/  
#include <assert.h>    /*assert 	 	*/ 	

#include "cbuffer.h"

#define DUMMY 1
#define TRUE 1

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
	assert(buffer);
	
	free(buffer);
}

size_t BufferRead(void *dest, buffer_t *buffer, size_t n)
{
    size_t read_elements = 0;	
    char *dest_ptr = NULL;
	
	assert(NULL != dest);
	assert(NULL != buffer);
	
	if (TRUE == BufferIsEmpty(buffer))
	{
		return (0);
	}
	
	if (n > BufferSize(buffer))
	{
		n = BufferSize(buffer);
	}
	
	read_elements = n;
	dest_ptr = (char *)dest;

	while (0 != n)
	{
		*dest_ptr = buffer->array[DUMMY + buffer->read];
		dest_ptr++;
		buffer->read++;
		n--;		
		if (buffer->read > buffer->capacity)
		{
			buffer->read = 0;
		}
	}
		
	return (read_elements);
}

size_t BufferWrite(const void *src, buffer_t *buffer, size_t n)
{
    size_t write_elements = 0;	
    char *src_ptr = NULL;
    
	assert(NULL != src);
	assert(NULL != buffer);
	
	if (0 == BufferFreeSpace(buffer))
	{
		return (0);
	}
	
	if (n > BufferFreeSpace(buffer))
	{
		n = BufferFreeSpace(buffer);
	}
	
	write_elements = n;
	
	src_ptr = (char *)src;

	while (0 != n)
	{
		buffer->array[DUMMY + buffer->write] = *src_ptr;
		src_ptr++;
		buffer->write++;
		n--;	
		if (buffer->write > buffer->capacity)
		{
			buffer->write = 0;
		}
	}
		
	return (write_elements);
}
	
size_t BufferSize(const buffer_t *buffer)
{
	size_t array_size = 0;
	
	array_size = ((buffer->write + buffer->capacity + DUMMY) - buffer->read)\
				 % (buffer->capacity + DUMMY);
	
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
