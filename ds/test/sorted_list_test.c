/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stdio.h>  /*printf*/

#include "sorted_list.h"
#include "dll.h"

#define TRUE 1
#define FALSE 0

static void TestSortedList();

int main()
{
	TestSortedList();

	return (0);
}

static void PrintSortedList(sorted_list_t *sorted_list)
{
	sorted_iter_t runner;
	size_t size = 0;
	size_t i = 0;
	void *data = NULL;
	
	size = SortedListSize(sorted_list);
	
	runner = SortedListBegin(sorted_list);
		
	for (i = 0; i < size; i++)
	{		
		data = SortedListGetData(runner);
		printf("%d\n", *(int *)data);
		runner = SortedListNext(runner);
	}
	printf("\n");
}

static void TestInt(int control, int test, int line)
{
	if (control != test)
	{
		printf("\033[0;31m");
		printf("Error. failed at line %d\n", line);
		printf("\033[0m"); 
	}
	else
	{
		printf("\033[1;32m");
		printf("Success!\n");
		printf("\033[0m"); 
	}
}

static int comp_func(void *node_data, void *parametr)
{
	return (*(int *)node_data - *(int *)parametr);
}

static void TestState(sorted_list_t *sorted_list, size_t control_size,\
				 	  int control_state)
{
	TestInt(control_size, SortedListSize(sorted_list), __LINE__);
	TestInt(control_state, SortedListIsEmpty(sorted_list), __LINE__);
}

static size_t TestInsert(sorted_list_t *sorted_list)
{
	static int data_array_1[] = {126, 23, 58, 15, -16, -666};
	size_t array_size = 0;
	size_t i = 0;

	array_size = sizeof(data_array_1) / sizeof(data_array_1[0]);
	
	for (i = 0; i < array_size; i++)
	{
		SortedListInsert(sorted_list, &data_array_1[i]);	
	}
	
	return (array_size);
}

static void TestMerge(sorted_list_t *sorted_list)
{
	sorted_list_t *merge_list;
	static int data_array_2[] = {0, 2, 1, 15, -100, -101, -99};
	size_t array_size = 0;
	size_t i = 0;
	
	merge_list = SortedListCreate(comp_func);

	array_size = sizeof(data_array_2) / sizeof(data_array_2[0]);
	
	for (i = 0; i < array_size; i++)
	{
		SortedListInsert(merge_list, &data_array_2[i]);	
	}
	
	SortedListMerge(sorted_list, merge_list);
	PrintSortedList(sorted_list);
	
	SortedListDestroy(merge_list);
}

static void TestSortedList()
{
	sorted_list_t *sorted_list;
	size_t list_size = 0;
	
	sorted_list = SortedListCreate(comp_func);
	TestState(sorted_list, 0, TRUE);
	
	list_size = TestInsert(sorted_list);
	TestState(sorted_list, list_size, FALSE);
	PrintSortedList(sorted_list);
	
	TestMerge(sorted_list);

	SortedListDestroy(sorted_list);
}














