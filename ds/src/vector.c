/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Yael Argov 
*Date: 04/12/2023
*******************************************************************************/
#include <string.h> /*memcpy*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "vector.h"

#define BYTE_SIZE(i) (i * vector->element_size * sizeof(char))
#define GROWTH_FACTOR 2
#define ERROR -1
#define SUCCESS 0
#define VECTOR_POINTER(a) (char *)(vector->array) + BYTE_SIZE(a)

struct vector
{
	void *array;
	size_t element_size;
	size_t current_size;
	size_t capacity;
};

static int ResizeArray(vector_t *vector, size_t new_size)
{
	void *temp_buffer = NULL;
	
	temp_buffer = realloc(vector->array, BYTE_SIZE(new_size));
	if (NULL == vector->array) 
    {
        return (ERROR); 
    }
    
    vector->array = temp_buffer;
    
    vector->capacity = new_size;
    
    return (SUCCESS);
}

vector_t *VectorCreate(size_t element_size, size_t initial_capacity)
{
	vector_t *vector = (vector_t *)malloc(sizeof(vector_t));
    if (NULL == vector) 
    {
        return (NULL);
    }
	
	assert(0 != initial_capacity);
	assert(0 != element_size);
	
	vector->element_size = element_size;
	vector->current_size = 0;
	vector->capacity = initial_capacity;
	vector->array = malloc(BYTE_SIZE(initial_capacity));
	if (NULL == vector->array)
	{
		free(vector);
		
		return (NULL); 
	}
	
	return (vector);
}

void VectorDestroy(vector_t *vector)
{
	free(vector->array);
	vector->array = NULL;
	
	free(vector);
}

void *VectorGetAccess(vector_t *vector, size_t index)
{
	assert(NULL != vector);
	assert((vector->current_size) > index); 
	
	return (VECTOR_POINTER(index)); 
}

int VectorPushBack(vector_t *vector, const void *data)
{
	size_t element_size = 0;
	size_t current_size = 0;
	
	assert(NULL != vector);
	assert(NULL != data);
	
	element_size = vector->element_size;
	current_size = vector->current_size;

	memcpy(VECTOR_POINTER(current_size), data, element_size);
	
	vector->current_size++;
			
	if (vector->current_size == vector->capacity)
	{
		return (VectorReserve(vector, vector->capacity * GROWTH_FACTOR));
	}
	
	return (SUCCESS);
}

int VectorPopBack(vector_t *vector) 
{
	assert(NULL != vector);
	
	vector->current_size--;
	
	if (vector->current_size < (vector->capacity / GROWTH_FACTOR))
	{
		return (VectorShrink(vector));
	}

	return (SUCCESS);
}

size_t VectorSize(const vector_t *vector)
{
	assert(NULL != vector);
	
	return (vector->current_size);
}

size_t VectorCapacity(const vector_t *vector)
{
	assert(NULL != vector);
	
	return (vector->capacity);
}

int VectorShrink(vector_t *vector)
{
	assert(NULL != vector);
	
	return (ResizeArray(vector, vector->current_size));
}

int VectorReserve(vector_t *vector, size_t new_capacity)
{
	assert(NULL != vector);

	return (ResizeArray(vector, new_capacity));
}
