/*******************************************************************************
*Author: Arieh Farber 
*Reviewer:  
*Date: 
*******************************************************************************/
#include <stdio.h> 	   /*BUFSIZ		 */
#include <stdlib.h>    /*malloc, free*/ 
#include <stddef.h>    /*size_t  	 */

#include "cbuffer.h"

static void TestBuffer();

int main()
{
	TestBuffer();
	
	return (0);
}

static void TestBuffer()
{
	buffer_t *buffer = NULL;
	char *dest = NULL;
	char *src = "abcd";
	size_t n_write = 3;
	size_t n_read = 15;
	size_t capacity = 5;
	int i = capacity;

	buffer = BufferCreate(capacity);
	
	n_write = BufferWrite(src, buffer, n_write);
	printf("n_write is %lu\n", n_write);
	
	dest = malloc(capacity);
	n_read = BufferRead(dest, buffer, n_read);
	printf("n_read is %lu\n", n_read);
	
	while (0 != i)
	{
		printf("%c\n", dest[i]);
		i--;
	}
	
		
	BufferDestroy(buffer);
	
	free(dest);
}
