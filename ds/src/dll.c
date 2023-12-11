/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert	  */

#include "dll.h"

#define TRUE 1

struct node
{
	void *data;
	struct node *next;
	struct node *prev;
};

struct dll
{
	struct node head;
	struct node tail;
};

dll_t *DLLCreate(void)
{
	dll_t *dll = (dll_t *)malloc(sizeof(dll_t));
    if (NULL == dll) 
    {
        return (NULL);
    }
    
    dll->head.data = NULL;
    dll->head.next = &dll->tail;
    dll->head.prev = NULL;

    dll->tail.data = NULL;
    dll->tail.next = NULL;
    dll->tail.prev = &dll->head;
  
	return (dll);
}

void DLLDestroy(dll_t *dll)
{
	dll_iter_t *runner = NULL;
	dll_iter_t *end_node = NULL;
	
	assert(NULL != dll);
	
	runner = DLLBegin(dll);
	end_node = DLLEnd(dll);
	
	while (TRUE != DLLIsEqual(runner, end_node))
	{
		runner = DLLRemove(runner);
	}
	
	free(dll);
}

int DLLIsEmpty(const dll_t *dll)
{
	return (dll->head.next == &dll->tail);
}

size_t DLLSize(const dll_t *dll)
{
	size_t count = 0;
	dll_iter_t *runner = NULL;
	dll_iter_t *end_node = NULL;
	
	runner = DLLBegin(dll);
	end_node = DLLEnd(dll);
	
	while (TRUE != DLLIsEqual(runner, end_node))
	{
		runner = DLLNext(runner);
		count++;
	}
	
	return (count);
}

void *DLLGet(const dll_iter_t *iter)
{
	assert(NULL != iter);
	
	return ((void *)iter->data);
}

void DLLSet(dll_iter_t *iter, void *data)
{
	assert(NULL != iter);
	
	iter->data = data;
}

dll_iter_t *DLLInsert(dll_iter_t *iter, void *data)
{
    dll_iter_t *new_node = NULL;

    assert(NULL != iter);

    new_node = (dll_iter_t *)malloc(sizeof(dll_iter_t));
    if (NULL == new_node)
    {
        return (NULL);
    }

    new_node->data = data;
    new_node->next = iter;
    new_node->prev = iter->prev;
    
    iter->prev->next = new_node;
    iter->prev = new_node;
  
    return (iter);	
}

dll_iter_t *DLLRemove(dll_iter_t *iter)
{
	dll_iter_t *next_node = NULL;
	
    assert(NULL != iter);
    
    next_node = DLLNext(iter);
    
    free(iter);
    
    return (next_node);
}

dll_iter_t *DLLPushback(dll_t *dll, void *data)
{
	return (DLLInsert(DLLEnd(dll), data));
}

dll_iter_t *DLLPushfront(dll_t *dll, void *data)
{
	return (DLLInsert(DLLBegin(dll), data));
}

dll_iter_t *DLLPopback(dll_t *dll)
{

}

/*dll_iter_t *DLLPopfront(dll_t *dll);	*/

dll_iter_t *DLLPrev(const dll_iter_t *iter)
{
	assert(NULL != iter->prev);
	
	return ((dll_iter_t *)iter->prev);
}

dll_iter_t *DLLNext(const dll_iter_t *iter)
{
	assert(NULL != iter->next);
	
	return ((dll_iter_t *)iter->next);
}

dll_iter_t *DLLBegin(const dll_t *dll)
{
	assert(NULL != dll);
	
	return (dll->head.next);
}

dll_iter_t *DLLEnd(const dll_t *dll)
{
	assert(NULL != dll);
	
	return ((dll_iter_t *)&dll->tail);
}

int DLLIsEqual(dll_iter_t *iter1, dll_iter_t *iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);
	
	return (iter1 == iter2);
}

















