/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Bar Gonen
*Date: 03/12/2023
*******************************************************************************/
#include <string.h> /*memcpy*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "stack.h"
#include "ds_utils.h" /*TRUE*/

#define EMPTY 0

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

	stack->buffer = malloc(capacity * element_size * sizeof(char));
	if (NULL == stack->buffer)
	{
		free (stack);
		
		return (NULL);
	}
	
	stack->element_size = element_size;
	stack->current_size = 0;
	stack->capacity = capacity;
	
	return (stack);
}

void StackDestroy(stack_t *stack)
{
	while (TRUE != StackIsEmpty(stack))
	{
		StackPop(stack);
	}
	
	free(stack->buffer);
	
	free(stack);
}

void StackPush(stack_t *stack, const void *data)
{
	assert(NULL != stack);
	assert(NULL != data);
	assert((stack->capacity) > (stack->current_size));
		
	memcpy(stack->buffer, data, stack->element_size);
	
	stack->buffer += stack->element_size;
	
	++stack->current_size;
}

void StackPop(stack_t *stack)
{
	assert(NULL != stack);
	assert(EMPTY != stack->current_size);		
	
	stack->buffer -= stack->element_size;

	--stack->current_size;
}

void *StackPeek(const stack_t *stack)
{
	assert(NULL != stack);
	assert(EMPTY != stack->current_size);
		
	return ((void *)(stack->buffer - stack->element_size));
}

int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);
	
	return (EMPTY == StackSize(stack));
}

size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);
	
	return (stack->current_size);
}

size_t StackCapacity(const stack_t *stack)
{
	assert(NULL != stack);
	
	return (stack->capacity);
}
