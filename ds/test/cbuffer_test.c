/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Yael Argov
*Date: 11/12/2023
*******************************************************************************/
#include <stdio.h>	/*printf	  */ 	  
#include <stdlib.h> /*malloc, free*/ 
#include <stddef.h> /*size_t  	  */

#include "cbuffer.h"

#define TRUE 1
#define FALSE 0

static void TestBuffer();

int main()
{
	TestBuffer();
	
	return (0);
}

void TestInt(int control, int test, int line)
{
	if (control != test)
	{
		printf("\033[0;31m");
		printf("Error. failed at line %d\n", line);
		printf("\033[0m"); 
	}
	else
	{
		printf("\033[1;32m");
		printf("Success!\n");
		printf("\033[0m"); 
	}
}

void TestSizeT(size_t control, size_t test, int line)
{
	if (control != test)
	{
		printf("\033[0;31m");
		printf("Error. failed at line %d\n", line);
		printf("\033[0m"); 
	}
	else
	{
		printf("\033[1;32m");
		printf("Success!\n");
		printf("\033[0m"); 
	}
}

static void TestBufferWrite(buffer_t *buffer, size_t n)
{
	char *src = "abcdefghijklmnop";
	size_t control = 0;
	
	control = n;
	
	n = BufferWrite(src, buffer, n);
	
	TestSizeT(control, n, __LINE__);
}

static void TestBufferRead(void *dest, buffer_t *buffer, size_t n)
{
	size_t control = 0;
	
	control = n;
	
	n = BufferRead(dest, buffer, n);
	TestSizeT(control, n, __LINE__);
}

static void TestBufferStatus(buffer_t *buffer, size_t capacity)
{
	size_t size = 0;
	size_t free_space = 0;
	
	size = BufferSize(buffer);
	free_space = BufferFreeSpace(buffer);
	
	TestSizeT(size, (capacity - free_space), __LINE__);
}

static void TestBuffer()
{
	buffer_t *buffer = NULL;
	void *dest = NULL;
	size_t capacity = 6;
	
	dest = calloc(capacity, sizeof(char));

	buffer = BufferCreate(capacity);
	TestInt(TRUE, BufferIsEmpty(buffer), __LINE__);
	TestBufferStatus(buffer, capacity);
	
	TestBufferWrite(buffer, 4);
	TestInt(FALSE, BufferIsEmpty(buffer), __LINE__);
	TestBufferStatus(buffer, capacity);
	
	TestBufferRead(dest, buffer, 2);
	
	TestBufferWrite(buffer, 4);
	TestInt(FALSE, BufferIsEmpty(buffer), __LINE__);
	TestBufferStatus(buffer, capacity);
	
	TestBufferRead(dest, buffer, 2);
	TestInt(FALSE, BufferIsEmpty(buffer), __LINE__);
	TestBufferStatus(buffer, capacity);

	BufferDestroy(buffer);
	
	free(dest);
}





