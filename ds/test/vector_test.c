/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Yael Argov 
*Date: 04/12/2023
*******************************************************************************/
#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/

#include "vector.h"

static void TestVector();

int main()
{
	TestVector();
	
	return (0);
}

static void PrintStatus(vector_t *vector, int status);
static void PrintPointer(vector_t *vector, size_t index);

static void TestVector()
{
	vector_t *test_vector;
	int value = 0;
	size_t initial_capacity = 2;
	size_t element_size = sizeof(int);
	size_t i = 0;
	int status = 0;
	size_t new_capacity = 0;
	
	test_vector = VectorCreate(element_size, initial_capacity);
	assert(NULL != test_vector);
	
	for (i = 0; i < initial_capacity * 2; i++) 
	{
		value = 101 + i;
		status = VectorPushBack(test_vector, &value);
		PrintStatus(test_vector, status);
		PrintPointer(test_vector, i);
	}
	
	for (i = 0; i < initial_capacity; i++) 
	{
		value = 1 + i;
		status = VectorPopBack(test_vector);
		PrintStatus(test_vector, status);
		PrintPointer(test_vector, i);
	}
	
	new_capacity = 100;
	status = VectorReserve(test_vector, new_capacity);
	PrintStatus(test_vector, status);

	VectorDestroy(test_vector);
}


static void PrintStatus(vector_t *vector, int status)
{	
	printf("Vector size is %lu, ", VectorSize(vector));
	printf("Vector capacity is %lu, ", VectorCapacity(vector));
	printf("Vector status is %d\n", status);
}

static void PrintPointer(vector_t *vector, size_t index)
{	
	printf("Vector pointer is %p, ", VectorGetAccess(vector, index));
	printf("Pointer value is %d\n\n", *(int *)VectorGetAccess(vector, index));
}
