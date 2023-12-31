/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Omer Bruker
*Date: 12/12/2023
*******************************************************************************/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert	  */

#include "dll.h"

#define ERROR -1
#define SUCCESS 0
#define TRUE 1
#define FALSE 0

struct node
{
	void *data;
	dll_iter_t next;
	dll_iter_t prev;
};

struct dll
{
	struct node head;
	struct node tail;
};

static int ActCount(void *node_data, void *parametrs);

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
	dll_iter_t runner = NULL;
	
	assert(NULL != dll);
	
	runner = DLLBegin(dll);
	
	while (TRUE != DLLIsEqual(runner, DLLEnd(dll)))
	{
		runner = DLLRemove(runner);
	}
	
	free(dll);
}

int DLLIsEmpty(const dll_t *dll)
{
	return (DLLIsEqual(DLLBegin(dll), DLLEnd(dll)));
}


size_t DLLSize(const dll_t *dll)
{
	size_t count = 0;
	
	DLLForEach(DLLBegin(dll), DLLEnd(dll), ActCount, &count);
	
	return (count);
}

void *DLLGet(const dll_iter_t iter)
{
	assert(NULL != iter);
	
	return ((void *)iter->data);
}

void DLLSet(dll_iter_t iter, void *data)
{
	assert(NULL != iter);
	
	iter->data = data;
}

dll_iter_t DLLInsert(dll_t *dll, dll_iter_t iter, void *data)
{  
    dll_iter_t new_node = NULL;

	assert(NULL != dll);
    assert(NULL != iter);

    new_node = (dll_iter_t)malloc(sizeof(struct node));
    if (NULL == new_node)
    {
        return (DLLEnd(dll));
    }

    new_node->data = data;
    new_node->next = iter;
    new_node->prev = DLLPrev(iter); 
    
    iter->prev->next = new_node;
    iter->prev = new_node;
  
    return (new_node);	
}

dll_iter_t DLLRemove(dll_iter_t iter)
{
	dll_iter_t next_node = NULL;
	
    assert(NULL != iter->next);
    
	next_node = DLLNext(iter); 
	    
    iter->prev->next = DLLNext(iter);
    iter->next->prev = DLLPrev(iter);
	
    free (iter);
    
    return (next_node);
}

dll_iter_t DLLPushback(dll_t *dll, void *data)
{
	assert(NULL != dll);
	
	return (DLLInsert(dll, DLLEnd(dll), data));
}

dll_iter_t DLLPushfront(dll_t *dll, void *data)
{
	assert(NULL != dll);
	
	return (DLLInsert(dll, DLLBegin(dll), data));
}

void *DLLPopback(dll_t *dll)
{
	void *temp_data = NULL;
	
	assert(NULL != dll);
	
	temp_data = DLLGet(DLLPrev(DLLEnd(dll)));
	
	DLLRemove(DLLPrev(DLLEnd(dll))); 
	
	return (temp_data);
}

void *DLLPopfront(dll_t *dll)
{
	void *temp_data = NULL;
	
	assert(NULL != dll);
	
	temp_data = DLLGet(DLLBegin(dll));

	DLLRemove(DLLBegin(dll)); 

	return (temp_data);
}

dll_iter_t DLLPrev(const dll_iter_t iter)
{
	assert(NULL != iter->prev); 
	
	return ((dll_iter_t )iter->prev);
}

dll_iter_t DLLNext(const dll_iter_t iter)
{
	assert(NULL != iter->next);
	
	return ((dll_iter_t )iter->next);
}

dll_iter_t DLLBegin(const dll_t *dll)
{
	assert(NULL != dll);
	
	return (dll->head.next);
}

dll_iter_t DLLEnd(const dll_t *dll)
{
	assert(NULL != dll);
	
	return ((dll_iter_t )&dll->tail);
}

int DLLIsEqual(dll_iter_t iter1, dll_iter_t iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);
	
	return (iter1 == iter2);
}

int DLLForEach(dll_iter_t from, dll_iter_t to, action_t act_func,\
			   void *params)
{
	int status = SUCCESS;	
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != act_func);
	
	while (TRUE != DLLIsEqual(from, to) && SUCCESS == status) 
	{
		status = act_func(from->data, params);
		from = DLLNext(from);
	}

	return (status);
}

dll_iter_t DLLFind(dll_iter_t from, dll_iter_t to, is_match_t is_match_func,\
					void *params)
{
	assert(NULL != from);
	assert(NULL != to);
	
	while (TRUE != DLLIsEqual(from, to)) 
	{
		if (TRUE == is_match_func(from->data, params))
		{
			return (from);
		}
		from = DLLNext(from);
	}
	
	return (to);
}

void DLLSplice(dll_iter_t from, dll_iter_t to, dll_iter_t where)
{
	dll_iter_t temp_node = NULL;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != where);
	
	temp_node = DLLPrev(where);
	where->prev->next = from;
	to->prev->next = where;
	where->prev = DLLPrev(to); 
	to->prev = DLLPrev(from); 
	from->prev->next = to;
	from->prev = temp_node;
}

int DLLMultiFind(dll_iter_t from, dll_iter_t to, is_match_t is_match_func,\
				 void *params, dll_t *output)
{
	dll_iter_t runner = NULL;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != output);
	
	while (TRUE != DLLIsEqual(from, to)) 
	{
		if (TRUE == is_match_func(from->data, params))
		{
			runner = DLLInsert(output, DLLEnd(output), params);
			if (NULL == runner)
			{
				return (ERROR);
			}
		}
		from = DLLNext(from);
	}
	
	return (SUCCESS);
}

static int ActCount(void *node_data, void *parametrs)
{
	*(size_t *)parametrs += 1;
	(void)node_data;
	
	return (SUCCESS);
}
