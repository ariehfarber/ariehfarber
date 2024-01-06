/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Bar Gonen
*Date: 14/12/2023
*******************************************************************************/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert	  */

#include "sorted_list.h"
#include "ds_utils.h" /*TRUE, FALSE, SUCCESS*/

#define FAIL 1
#define ERROR -1

struct sorted_list
{
	compare_t compare;
	dll_t *dll;
};

typedef struct find_params
{
	compare_t compare;
	void *data;
} find_params_t;

static dll_t *FetchDLL(sorted_list_t *sorted_list);
#ifndef NDEBUG
static sorted_list_t *FetchSortedList(sorted_iter_t iter);
#endif
static int IsMatchFindParams(void *data, void *params);
static dll_iter_t FindInsertLocation(sorted_list_t *sorted_list, void *data);

sorted_list_t *SortedListCreate(compare_t comp_func)
{
	sorted_list_t *sorted_list = NULL;
	
	sorted_list = (sorted_list_t *)malloc(sizeof(sorted_list_t));
	if (NULL == sorted_list)
	{
		return (NULL);
	}
	
	sorted_list->dll = DLLCreate();
	if (NULL == FetchDLL(sorted_list))
	{
		free(sorted_list);
		return (NULL);
	}
	
	sorted_list->compare = comp_func;
	
	return (sorted_list);
}

void SortedListDestroy(sorted_list_t *sorted_list)
{
	DLLDestroy(FetchDLL(sorted_list));
	
	free (sorted_list);
}

int SortedListIsEmpty(const sorted_list_t *sorted_list)
{
	assert(NULL != sorted_list);
	
	return (DLLIsEmpty(FetchDLL((sorted_list_t *)sorted_list))); 
}

size_t SortedListSize(const sorted_list_t *sorted_list)
{
	assert(NULL != sorted_list);
	
	return (DLLSize(FetchDLL((sorted_list_t *)sorted_list)));
}

void *SortedListGetData(sorted_iter_t iter)
{
	return (DLLGet(iter.iter)); 
}

sorted_iter_t SortedListInsert(sorted_list_t *sorted_list, void *data)
{
	dll_iter_t where = NULL;
	sorted_iter_t location = {0};
	
	assert(NULL != sorted_list);
	
	where = FindInsertLocation(sorted_list, data);
	location.iter = DLLInsert(FetchDLL(sorted_list), where, data);
	#ifndef NDEBUG
	location.sorted_list = sorted_list;
	#endif
			
	return (location);
}

sorted_iter_t SortedListRemove(sorted_iter_t iter)
{
	iter.iter = DLLRemove(iter.iter);
	
	return (iter);
}

void *SortedListPopFront(sorted_list_t *sorted_list)
{
	assert(NULL != sorted_list);
	
	return (DLLPopfront(FetchDLL(sorted_list)));
}

void *SortedListPopBack(sorted_list_t *sorted_list)
{
	assert(NULL != sorted_list);
	
	return (DLLPopback(FetchDLL(sorted_list)));
}

void SortedListMerge(sorted_list_t *dest, sorted_list_t *src)
{
	dll_iter_t to_src = NULL;
	dll_iter_t where_dest = NULL;
	
	assert(NULL != dest);
	assert(FetchDLL(dest) != FetchDLL(src));
	
	to_src = DLLBegin(src->dll);

	while (TRUE != DLLIsEqual(to_src, DLLEnd(src->dll)))
	{
		where_dest = FindInsertLocation(dest, DLLGet(DLLBegin(src->dll)));
		if (TRUE == DLLIsEqual(where_dest, DLLEnd(dest->dll)))
		{
			to_src = DLLEnd(src->dll);
		}
		else
		{
			to_src = FindInsertLocation(src, DLLGet(where_dest));
		}	
		DLLSplice(DLLBegin(src->dll), to_src, where_dest);
	}
}

sorted_iter_t SortedListBegin(const sorted_list_t *sorted_list)
{
	sorted_iter_t start_iter = {0};
	
	assert(NULL != sorted_list);
	
	start_iter.iter = DLLBegin(FetchDLL((sorted_list_t *)sorted_list));
	#ifndef NDEBUG
	start_iter.sorted_list = (sorted_list_t *)sorted_list;
	#endif
	
	
	return (start_iter);	
}

sorted_iter_t SortedListEnd(const sorted_list_t *sorted_list)
{
	sorted_iter_t end_iter = {0};
	
	assert(NULL != sorted_list);
	
	end_iter.iter = DLLEnd(FetchDLL((sorted_list_t *)sorted_list));
	#ifndef NDEBUG
	end_iter.sorted_list = (sorted_list_t *)sorted_list;
	#endif
	
	return (end_iter);
}

sorted_iter_t SortedListPrev(sorted_iter_t iter)
{
	iter.iter = DLLPrev(iter.iter);
	
	return (iter);
}

sorted_iter_t SortedListNext(sorted_iter_t iter)
{
	iter.iter = DLLNext(iter.iter);
	
	return (iter);
}

int SortedListIsEqual(sorted_iter_t iter1, sorted_iter_t iter2)
{
	return (DLLIsEqual(iter1.iter, iter2.iter));
}

int SortedListForEach(sorted_iter_t from, sorted_iter_t to,\
					  action_t act_func, void *params)
{
	assert(NULL != act_func);
	#ifndef NDEBUG
	if (FetchSortedList(from) != FetchSortedList(to))
	{
		return (ERROR);
	}
	#endif	
	
	return (DLLForEach(from.iter, to.iter, act_func, params));
}

sorted_iter_t SortedListFind(sorted_iter_t from, sorted_iter_t to,\
							 void *to_find, const sorted_list_t *sorted_list)
{
	find_params_t params = {0};
	sorted_iter_t location = {0};
	
	assert(NULL != sorted_list);
	#ifndef NDEBUG
	if (FetchSortedList(from) != FetchSortedList(to))
	{
		return (to);
	}
	#endif	
	
	params.compare = sorted_list->compare;
	params.data = to_find;
	
	location = SortedListFindIf(from, to, IsMatchFindParams, &params);
	
	return (location);
}

sorted_iter_t SortedListFindIf(sorted_iter_t from, sorted_iter_t to,\
 								 is_match_t is_match_func, void *params)
{
	sorted_iter_t location = {0};
	
	assert(NULL != is_match_func);
	#ifndef NDEBUG
	if (FetchSortedList(from) != FetchSortedList(to))
	{
		return (to);
	}
	#endif	
	
	location.iter = DLLFind(from.iter, to.iter, is_match_func, params);
	
	return (location);
}

static dll_t *FetchDLL(sorted_list_t *sorted_list)
{
	assert(NULL != sorted_list);
	
	return (sorted_list->dll);
}

#ifndef NDEBUG
static sorted_list_t *FetchSortedList(sorted_iter_t iter)
{
	return (iter.sorted_list);
}
#endif

static int IsMatchFindParams(void *data, void *params)
{
	return (0 == ((find_params_t *)params)->compare\
		   (((find_params_t *)params)->data, data));
}

static dll_iter_t FindInsertLocation(sorted_list_t *sorted_list, void *data)
{
	dll_iter_t from = NULL;
	dll_iter_t to = NULL;
	
	from = DLLBegin(FetchDLL(sorted_list));
	to = DLLEnd(FetchDLL(sorted_list));
	
	while (TRUE != DLLIsEqual(from, to) && \
	0 >= sorted_list->compare(DLLGet(from), data)) 
	{
		from = DLLNext(from);
	}
	
	return (from);
}
