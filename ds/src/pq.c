/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Omer Bruker 
*Date: 21/12/2023
*******************************************************************************/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert	  */

#include "pq.h"
#include "sorted_list.h"
#include "ds_utils.h" /*TRUE, FALSE, SUCCESS*/

#define ERROR -1

struct pq
{
	sorted_list_t *sorted_list;
};

static sorted_list_t *FetchSortedList(pq_t *pq);

pq_t *PQCreate(pq_compare_t compare_func)
{
	pq_t *pq = NULL;
	
	assert(NULL != compare_func);
	
	pq = (pq_t *)malloc(sizeof(pq_t));
	if (NULL == pq)
	{
		return (NULL);
	}
	
	pq->sorted_list = SortedListCreate(compare_func);
	if (NULL == FetchSortedList(pq))
	{
		free(pq);
		return (NULL);
	}
	
	return (pq);
}

void PQDestroy(pq_t *pq)
{
	SortedListDestroy(FetchSortedList(pq));
	
	free(pq);
}

int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);
	
	return (SortedListIsEmpty(FetchSortedList((pq_t *)pq)));
}

size_t PQSize(const pq_t *pq)
{
	assert(NULL != pq);
	
	return (SortedListSize(FetchSortedList((pq_t *)pq)));
}

int PQEnqueue(pq_t *pq, void *data)
{
	int state = SUCCESS;
	
	assert(NULL != pq);
	
	if (TRUE == SortedListIsEqual(SortedListEnd(FetchSortedList(pq)), \
								  SortedListInsert(FetchSortedList(pq), data)))
	{
		state = ERROR;
	}
	
	return (state);
}

void *PQDequeue(pq_t *pq)
{
	assert(NULL != pq);

	return (SortedListPopFront(FetchSortedList(pq)));
}

void *PQPeek(const pq_t *pq)
{
	assert(NULL != pq);
		
	return (SortedListGetData(SortedListBegin(FetchSortedList((pq_t *)pq))));
}

void PQClear(pq_t *pq)
{
	assert(NULL != pq);
	
	while (TRUE != SortedListIsEmpty(FetchSortedList(pq)))
	{
		PQDequeue(pq);
	}
}

void *PQErase(pq_t *pq, pq_is_match_t is_match_func, void *params)
{
	sorted_iter_t start = {0};
	sorted_iter_t end = {0};
	sorted_iter_t temp_iter = {0};	
	void *data = NULL;
	
	assert(NULL != pq);
	assert(NULL != is_match_func);
	
	start = SortedListBegin(FetchSortedList(pq));
	end = SortedListEnd(FetchSortedList(pq));
	
	temp_iter = SortedListFindIf(start, end, is_match_func, params);
	if (TRUE == SortedListIsEqual(temp_iter, end))	
	{
		return (NULL);
	}			 			 
	
	data = SortedListGetData(temp_iter);
	
	SortedListRemove(temp_iter);				 			 
	
	return (data);
}

static sorted_list_t *FetchSortedList(pq_t *pq)
{
	assert(NULL != pq);
	
	return (pq->sorted_list);
}
