/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
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
	stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
    if (NULL == stack) 
    {
        return (NULL);
    }
	
	assert(0 != capacity);
	assert(0 != element_size);

	stack->buffer = malloc(capacity * element_size);
	if (NULL == stack->buffer)
	{
		return (NULL);
	}
	
	stack->element_size = element_size;
	stack->current_size = 0;
	stack->capacity = capacity;
	
	return (stack);
}

void StackDestroy(stack_t *stack)
{
	while (1 != stack->current_size)
	{
		stack->buffer -= stack->element_size;
		stack->current_size--;
	}
	
	free(stack->buffer);
	stack->buffer = NULL;
	
	free(stack);
	stack = NULL;
}

void StackPush(stack_t *stack, const void *data)
{
	assert(NULL != stack);
	assert(NULL != data);
	assert((stack->capacity) > (stack->current_size));
	
	if (0 != stack->current_size)
	{
		stack->buffer += stack->element_size;
	}
	
	memcpy(stack->buffer, data, stack->element_size);
	
	stack->current_size++;
}

void StackPop(stack_t *stack)
{
	assert(NULL != stack);
	assert(0 != stack->current_size);		
	
	stack->buffer -= stack->element_size;

	stack->current_size--;
}

void *StackPeek(const stack_t *stack)
{
	void *peek_ptr = NULL;
	
	assert(NULL != stack);
	assert(0 != stack->current_size);
	
	peek_ptr = (void *)stack->buffer;
	
	return (peek_ptr);
}

int StackIsEmpty(const stack_t *stack)
{
	return (stack->current_size == 0);
}

size_t StackSize(const stack_t *stack)
{
	return (stack->current_size);
}

size_t StackCapacity(const stack_t *stack)
{
	return (stack->capacity);
}














