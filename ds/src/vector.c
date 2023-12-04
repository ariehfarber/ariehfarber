/*******************************************************************************
*Author: Arieh Farber 
*Reviewer:  
*Date: 
*******************************************************************************/
#include <string.h> /*memcpy*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "vector.h"

#define STEP(i) (i * vector->element_size * sizeof(char))
#define GROWTH_FACTOR 2
#define ERROR -1
#define SUCCESS 0

struct vector
{
	void *array;
	size_t element_size;
	size_t current_size;
	size_t capacity;
};

static int ResizeArray(vector_t *vector, size_t new_size)
{
	vector->array = realloc(vector->array, STEP(new_size));
	if (NULL == vector->array) 
    {
        return (ERROR);
    }
    
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

	vector->array = malloc(initial_capacity * element_size * sizeof(char));
	if (NULL == vector->array)
	{
		return (NULL);
	}
	
	vector->element_size = element_size;
	vector->current_size = 0;
	vector->capacity = initial_capacity;
	
	return (vector);
}

void VectorDestroy(vector_t *vector)
{
	free(vector->array);
	vector->array = NULL;
	
	free(vector);
	vector = NULL;
}

void *VectorGetAccess(vector_t *vector, size_t index)
{
	assert(NULL != vector);
	assert((vector->capacity) > index);
	
	return ((char *)(vector->array) + STEP(index));
}

int VectorPushBack(vector_t *vector, const void *data)
{
	size_t element_size = 0;
	size_t current_size = 0;
	
	assert(NULL != vector);
	assert(NULL != data);
	assert(vector -> current_size < vector -> capacity);
	
	element_size = vector->element_size;
	current_size = vector->current_size;

	memcpy((char *)(vector->array) + STEP(current_size), data, element_size);
	
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
