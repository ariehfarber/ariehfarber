/*******************************************************************************
*Author: Arieh Farber 
*Reviewer:  
*Date: 
*******************************************************************************/
#include <assert.h> /*assert	  */
#include <stdlib.h> /*calloc, free*/
#include <math.h>   /*pow		  */

#include "sort.h"

#define SUCCESS 0
#define ERROR -1

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
	int max = 0;
	int i = 0, j = 0;
	int *count_arr = NULL;
	
	assert(NULL != arr);
	
	max = FindMax(arr, arr_size) + 1;
	
	count_arr = calloc(max, sizeof(int));
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
	
	assert(NULL != arr);
	
	digits_num = CountDigitsInt(FindMax(arr, arr_size));
	
	while (Exponent <= digits_num)
	{
		
		++Exponent;
	}
	  

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


