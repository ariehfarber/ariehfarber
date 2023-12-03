/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stdio.h> /*printf*/

#include "stack.h"

static void TestStack();

int main()
{
	TestStack();
	
	return (0);
}

static void PrintIfStackIsEmpty(int boolean_value)
{
	if (boolean_value == 1)
	{
		printf("Stack check: the stack is empty\n");
	}
	else if (boolean_value == 0)
	{
		printf("Stack check: the stack is not empty\n");
	}
	else
	{
		printf("error with StackIsEmpty\n");
	}
	printf("\n");
}

static void TestStack()
{
	stack_t *test_stack;
	size_t capacity = 0;
	size_t element_size = 0;
	void *peek = NULL;
	int is_empty = -1;
	size_t current_size_of_stack = 0;
	size_t capacity_of_stack = 0;
	char values[] = {'a', 'r', 'i', 'e', 'h'};
	size_t i = 0;
	
	element_size = sizeof(char);
	capacity = sizeof(values) / sizeof(values[0]);
	
	test_stack = StackCreate(capacity, element_size);
	
	is_empty = StackIsEmpty(test_stack);
	PrintIfStackIsEmpty(is_empty);
	
	current_size_of_stack = StackSize(test_stack);
	printf("Current size of stack: %lu\n\n", current_size_of_stack);
	
	capacity_of_stack = StackCapacity(test_stack);
	printf("Capacity of stack: %lu\n\n", capacity_of_stack);
	
	printf("Pushing the stack - \n");
	for (i = 0; i < capacity; i++)
	{
		StackPush(test_stack, &values[i]);
		peek = StackPeek(test_stack);
		printf("peek %lu: %c\n", i, *(char *)peek);	
	}
	printf("\n");
	
	printf("Popping the stack - \n");
	for (i = capacity; 1 < i; i--)
	{
		peek = StackPeek(test_stack);
		printf("peek %lu: %c\n", i, *(char *)peek);	
		StackPop(test_stack);
	}
	printf("\n");
	
	current_size_of_stack = StackSize(test_stack);
	printf("Current size of stack: %lu\n\n", current_size_of_stack);

	is_empty = StackIsEmpty(test_stack);
	PrintIfStackIsEmpty(is_empty);
	
	StackDestroy(test_stack);
}











