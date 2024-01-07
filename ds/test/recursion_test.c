/*******************************************************************************
*Author: Arieh Farber 
*******************************************************************************/
#include <stdio.h> /*printf*/

#include "recursion.h"
#include "stack.h"
#include "ds_utils.h"

static void TestFibonacci();
static void TestSortStack();

int main()
{
    TestFibonacci();
    TestSortStack();

    return (0);
}

static void TestFibonacci()
{
    int element_index = 8;
    
    TestInt(IterativeFibonacci(element_index), \
    RecursiveFibonacci(element_index), __LINE__);
    printf("\n"); 
}

static void TestSortStack()
{
	stack_t *stack;
	int values[] = {98, 4, -6, 1, 66};
    size_t capacity = sizeof(values) / sizeof(values[0]);
	size_t element_size = sizeof(int);
	size_t i = 0;
	
	stack = StackCreate(capacity, element_size);
	
	for (i = 0; i < capacity; ++i)
	{
		StackPush(stack, &values[i]);
	}

    SortStack(stack);

    for (i = 0; i < capacity; ++i)
	{
		printf("%d\n", *(int *)StackPeek(stack));	
		StackPop(stack);
	}
	
	StackDestroy(stack);
}