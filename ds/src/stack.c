/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Bar Gonen
*Date: 03/12/2023
*******************************************************************************/
#include <string.h> /*memcpy*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "stack.h"

struct stack 
{
	char *buffer;
	size_t element_size;
	size_t current_size;
	size_t capacity;
};

stack_t *StackCreate(size_t capacity, size_t element_size)
{
	stack_t *my_stack = (stack_t *)malloc(sizeof(stack_t));
    if (NULL == my_stack) 
    {
        return (NULL);
    }
	
	assert(0 != capacity);
	assert(0 != element_size);

	my_stack->buffer = malloc(capacity * element_size * sizeof(char));
	if (NULL == my_stack->buffer)
	{
		return (NULL);
	}
	
	my_stack->element_size = element_size;
	my_stack->current_size = 0;
	my_stack->capacity = capacity;
	
	return (my_stack);
}

void StackDestroy(stack_t *my_stack)
{
	while (1 < my_stack->current_size)
	{
		my_stack->buffer -= my_stack->element_size;
		my_stack->current_size--;
	}
	
	free(my_stack->buffer);
	my_stack->buffer = NULL;
	
	free(my_stack);
	my_stack = NULL;
}

void StackPush(stack_t *my_stack, const void *data)
{
	assert(NULL != my_stack);
	assert(NULL != data);
	assert((my_stack->capacity) > (my_stack->current_size));
	
	if (0 != my_stack->current_size)
	{
		my_stack->buffer += my_stack->element_size;
	}
	
	memcpy(my_stack->buffer, data, my_stack->element_size);
	
	my_stack->current_size++;
}

void StackPop(stack_t *my_stack)
{
	assert(NULL != my_stack);
	assert(0 != my_stack->current_size);		
	
	my_stack->buffer -= my_stack->element_size;

	my_stack->current_size--;
}

void *StackPeek(const stack_t *my_stack)
{
	assert(NULL != my_stack);
	assert(0 != my_stack->current_size);
		
	return ((void *)my_stack->buffer);
}

int StackIsEmpty(const stack_t *my_stack)
{
	assert(NULL != my_stack);
	
	return (my_stack->current_size == 0);
}

size_t StackSize(const stack_t *my_stack)
{
	assert(NULL != my_stack);
	
	return (my_stack->current_size);
}

size_t StackCapacity(const stack_t *my_stack)
{
	assert(NULL != my_stack);
	
	return (my_stack->capacity);
}














