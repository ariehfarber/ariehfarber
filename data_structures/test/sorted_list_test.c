/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Bar Gonen
*Date: 14/12/2023
*******************************************************************************/
#include <stdio.h>  /*printf*/

#include "sorted_list.h"
#include "dll.h"
#include "ds_utils.h" /*TRUE, FALSE, SUCCESS, TestInt*/

#define ERROR -1

static void TestSortedList();

int main()
{
	TestSortedList();

	return (0);
}

static int CompFuncInt(void *node_data, void *parametr)
{
	return (*(int *)node_data - *(int *)parametr);
}

static int ActFuncInt(void *node_data, void *parametrs)
{
	*(int *)node_data = *(int *)parametrs;
	
	if (*(int *)node_data != *(int *)parametrs)
	{
		return (ERROR);
	}
	
	return (SUCCESS);
}

static int IsMatchInt(void *node_data, void *parametrs)
{
	if (*(int *)node_data == *(int *)parametrs)
	{
		return (TRUE);
	}
	
	return (FALSE);
}

static void TestState(sorted_list_t *sorted_list, size_t control_size,\
				 	  int control_state)
{
	TestInt(control_size, SortedListSize(sorted_list), __LINE__);
	TestInt(control_state, SortedListIsEmpty(sorted_list), __LINE__);
}

static size_t TestInsert(sorted_list_t *sorted_list)
{
	static int data_array_1[] = {1, 3, 5};
	size_t array_size = 0;
	size_t i = 0;

	array_size = sizeof(data_array_1) / sizeof(data_array_1[0]);
	
	for (i = 0; i < array_size; ++i)
	{
		SortedListInsert(sorted_list, &data_array_1[i]);	
	}
	
	return (array_size);
}

static void TestMerge(sorted_list_t *sorted_list)
{
	sorted_list_t *merge_list;
	static int data_array_2[] = {-12, -5, 1, 3, 9, 0};
	size_t array_size = 0;
	size_t i = 0;
	
	merge_list = SortedListCreate(CompFuncInt);

	array_size = sizeof(data_array_2) / sizeof(data_array_2[0]);
	
	for (i = 0; i < array_size; ++i)
	{
		SortedListInsert(merge_list, &data_array_2[i]);	
	}
	
	SortedListMerge(sorted_list, merge_list);
	
	SortedListDestroy(merge_list);
}

static void TestForEach(sorted_list_t *sorted_list)
{
	sorted_iter_t from;
	sorted_iter_t to;
	int state = 0;
	int params = 0;
	
	from = SortedListBegin(sorted_list);
	to = SortedListEnd(sorted_list);
	
	state = SortedListForEach(from, to, ActFuncInt, &params);
	TestInt(SUCCESS, state, __LINE__);
}
	
static void TestFind(sorted_list_t *sorted_list)
{
	sorted_iter_t from;
	sorted_iter_t to;
	int params = 3;
	
	from = SortedListBegin(sorted_list);
	to = SortedListEnd(sorted_list);
	
	from = SortedListFindIf(from, to, IsMatchInt, &params);
	TestInt(FALSE, SortedListIsEqual(from, to), __LINE__);
	
	from = SortedListBegin(sorted_list);
	to = SortedListEnd(sorted_list);
	
	from = SortedListFind(from, to, &params, sorted_list);
	TestInt(FALSE, SortedListIsEqual(from, to), __LINE__);
}

static void TestSortedList()
{
	sorted_list_t *sorted_list;
	size_t list_size = 0;
	
	sorted_list = SortedListCreate(CompFuncInt);
	TestState(sorted_list, 0, TRUE);
	
	list_size = TestInsert(sorted_list);
	TestState(sorted_list, list_size, FALSE);
	
	TestMerge(sorted_list);
	
	TestFind(sorted_list);
	
	TestForEach(sorted_list);
	
	SortedListDestroy(sorted_list);
}
