/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Elinor Fuchs
*Date: 01/01/2024
*******************************************************************************/
#include <assert.h> /*assert	  */
#include <stdlib.h> /*calloc, free*/
#include <math.h>   /*pow		  */

#include "sort.h"
#include "ds_utils.h" /*SUCCESS*/

#define ERROR -1

static int CountingSortForRadix(int *arr, size_t arr_size, int exp);
static void SwapInt(int *x, int *y);
static int FindMax(int *arr, size_t arr_size);
int CountDigitsInt(int n);

void BubbleSort(int *arr, size_t arr_size)
{
	size_t i = 0, j = 0;
	
	assert(NULL != arr);
	  
	for (i = 0; i < (arr_size - 1); ++i) 
	{  
    	for (j = 0; j < (arr_size - i - 1); ++j) 
    	{  
			if (arr[j] > arr[j + 1]) 
			{  
				SwapInt(&arr[j], &arr[j + 1]);
			}  
		}   
	}
}  

void SelectionSort(int *arr, size_t arr_size)
{
	size_t i = 0, j = 0;
	size_t min_index = 0;
	
	assert(NULL != arr);
	  
	for (i = 0; i < (arr_size - 1); ++i) 
	{  
		min_index = i;
    	for (j = i + 1; j < arr_size; ++j) 
    	{  
			if (arr[j] < arr[min_index])
			{
				min_index = j;
			}
		} 
		if (i != min_index)
		{
			SwapInt(&arr[min_index], &arr[i]);
		} 
	}
}

void InsertionSort(int *arr, size_t arr_size)
{
	size_t i = 0, j = 0;
	int key = 0;
	
	assert(NULL != arr);
	  
	for (i = 1; i < arr_size; ++i) 
	{  
		key = arr[i];
		j = i - 1;	
    	while (0 != j && key < arr[j])
    	{  
			arr[j + 1] = arr[j];
			--j;
		}   
		arr[j] = key;
	}
}

int CountingSort(int *arr, size_t arr_size)
{
	int max_value = 0;
	int i = 0, j = 0;
	int *count_arr = NULL;
	
	assert(NULL != arr);
	
	max_value = FindMax(arr, arr_size) + 1;
	
	count_arr = calloc(max_value, sizeof(int));
	if (NULL == count_arr)
	{
		return (ERROR);
	}
	
	for (i = 0; i < (int)arr_size; ++i)
	{
		++count_arr[arr[i]];
	}
	
	for (i = 0; i < (int)arr_size; ++i) 
	{
		while (0 == count_arr[j])
		{
			++j;
		}
		arr[i] = j;
		--count_arr[j];
	}
	
	free(count_arr);
	
	return (SUCCESS);
}

int RadixSort(int *arr, size_t arr_size)
{
	int digits_num = 0;
	int Exponent = 1;
	int state = SUCCESS;
	int i = 0;
	
	assert(NULL != arr);
	
	digits_num = CountDigitsInt(FindMax(arr, arr_size));
	
	for (i = 0; i < digits_num; ++i)
	{
		state = CountingSortForRadix(arr, arr_size, Exponent);
		if (ERROR == state)
		{
			break;
		}
		Exponent *= 10;
	}
	  
	return (state);
}

static int CountingSortForRadix(int *arr, size_t arr_size, int exp)
{
	int max_digits = 10;
	int i = 0;
	int *count_arr = NULL;
	int *output_array = NULL;
	
	assert(NULL != arr);
	
	count_arr = calloc(max_digits, sizeof(int));
	if (NULL == count_arr)
	{
		return (ERROR);
	}
	
	output_array = malloc(arr_size * sizeof(int));
	if (NULL == output_array)
	{
		free (count_arr);
		
		return (ERROR);
	}
	
	for (i = 0; i < (int)arr_size; ++i)
	{
		++count_arr[((arr[i] / exp) % 10)];
	}
	
	for (i = 1; i < max_digits; ++i)
	{
		count_arr[i] += count_arr[i - 1];
	}
	
	for (i = (int)arr_size - 1; i >= 0; --i) 
	{
		output_array[count_arr[((arr[i] / exp) % 10)] - 1] = arr[i];
		--count_arr[((arr[i] / exp) % 10)];
	}
	
	for (i = 0; i < (int)arr_size; ++i) 
	{
		arr[i] = output_array[i];
	}
	
	free(count_arr);
	free(output_array);
	
	return (SUCCESS);
}

static void SwapInt(int *x, int *y)
{
	int temp = *x;
	
	*x = *y;
	*y = temp;
}

static int FindMax(int *arr, size_t arr_size)
{
	size_t i = 0;
	size_t max_index = 0;
	
	max_index = i;
	for (i = 0; i < arr_size; ++i) 
	{  
		if (arr[i] > arr[max_index])
		{
			max_index = i;
		}
	}
	
	return (arr[max_index]); 
}

int CountDigitsInt(int n) 
{
	int count = 0;
	int temp = 1;

	while (temp <= n)
	{
		++count;
		temp *= 10;
	} 

	return (count);
}


