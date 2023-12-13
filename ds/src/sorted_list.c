/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert	  */

#include "sorted_list.h"
#include "dll.h"

#define SUCCESS 0
#define FAIL 1
#define ERROR -1
#define TRUE 1
#define FALSE 0

struct sorted_list
{
	compare_t compare;
	dll_t *dll;
};

sorted_list_t *SortedListCreate(compare_t comp_func)
{
	sorted_list_t *sorted_list = NULL;
	
	sorted_list = (sorted_list_t *)malloc(sizeof(sorted_list_t));
	if (NULL == sorted_list)
	{
		return (NULL);
	}
	
	sorted_list->dll = DLLCreate();
	if (NULL == sorted_list->dll)
	{
		return (NULL);
	}
	
	sorted_list->compare = comp_func;
	
	return (sorted_list);
}

void SortedListDestroy(sorted_list_t *sorted_list)
{
	DLLDestroy(sorted_list->dll);
	
	free (sorted_list);
}

int SortedListIsEmpty(const sorted_list_t *sorted_list)
{
	assert(NULL != sorted_list);
	
	return (DLLIsEmpty(sorted_list->dll)); 
}

size_t SortedListSize(const sorted_list_t *sorted_list)
{
	assert(NULL != sorted_list);
	
	return (DLLSize(sorted_list->dll));
}

void *SortedListGetData(sorted_iter_t iter)
{
	return (DLLGet(iter.iter)); 
}

static dll_iter_t InsertLocation(sorted_list_t *sorted_list, void *data)
{
	dll_iter_t from;
	dll_iter_t to;
	
	from = DLLBegin(sorted_list->dll);
	to = DLLEnd(sorted_list->dll);
	
	while (TRUE != DLLIsEqual(from, to) && \
	0 > sorted_list->compare(DLLGet(from), data)) 
	{
		from = DLLNext(from);
	}
	
	return (from);
}

sorted_iter_t SortedListInsert(sorted_list_t *sorted_list, void *data)
{
	dll_iter_t where;
	sorted_iter_t location;
	
	assert(NULL != sorted_list);
	
	where = InsertLocation(sorted_list, data);
	location.iter = DLLInsert(sorted_list->dll, where, data);
		
	return (location);
}

sorted_iter_t SortedListRemove(sorted_iter_t iter)
{
	sorted_iter_t next_iter;
	
	next_iter.iter = DLLRemove(iter.iter);
	
	return (next_iter);
}

void *SortedListPopFront(sorted_list_t *sorted_list)
{
	assert(NULL != sorted_list);
	
	return (DLLPopfront(sorted_list->dll));
}

void *SortedListPopBack(sorted_list_t *sorted_list)
{
	assert(NULL != sorted_list);
	
	return (DLLPopback(sorted_list->dll));
}

void SortedListMerge(sorted_list_t *dest, sorted_list_t *src)
{
	dll_iter_t from_src;
	dll_iter_t to_src;
	dll_iter_t where_dest;
	
	assert(NULL != dest);
	
	from_src = DLLBegin(src->dll);
	to_src = DLLBegin(src->dll);
	where_dest = DLLBegin(dest->dll);
	
	while (TRUE != DLLIsEqual(where_dest, DLLEnd(dest->dll)))
	{
		where_dest = InsertLocation(dest, DLLGet(from_src));
		
		to_src = InsertLocation(src, DLLGet(where_dest));
		
		DLLSplice(from_src, to_src, where_dest);
		
		from_src = to_src;		
	}
	
}

sorted_iter_t SortedListBegin(const sorted_list_t *sorted_list)
{
	sorted_iter_t start_iter;
	
	assert(NULL != sorted_list);
	
	start_iter.iter = DLLBegin(sorted_list->dll);
	
	return (start_iter);	
}

sorted_iter_t SortedListEnd(const sorted_list_t *sorted_list)
{
	sorted_iter_t end_iter;
	
	assert(NULL != sorted_list);
	
	end_iter.iter = DLLEnd(sorted_list->dll);
	
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

/*int SortedListForEach(sorted_iter_t from, sorted_iter_t to,\*/
/*					  action_t act_func, void *params)*/

/*sorted_iter_t SortedListFind(sorted_iter_t from, sorted_iter_t to,\*/
/*							 void *to_find, const sorted_list_t *sorted_list);*/

/*sorted_iter_t SortedListFindIf(sorted_iter_t from, sorted_iter_t to, is_match_t is_match_func, void *params);*/


