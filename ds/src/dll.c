/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert	  */

#include "dll.h"

#define ERROR -1
#define SUCCESS 0
#define TRUE 1

struct node
{
	void *data;
	dll_iter_t *next;
	dll_iter_t *prev;
};

struct dll
{
	dll_iter_t head;
	dll_iter_t tail;
};

static int ActCount(void *node_data, void *parametrs)
{
	*(size_t *)parametrs += 1;
	
	if (NULL == node_data)
	{
		return (ERROR);
	}
	
	return (SUCCESS);
}

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
	int state = 0;
	static size_t count = 0;
	dll_iter_t *start_node = NULL;
	dll_iter_t *end_node = NULL;
	
	start_node = DLLBegin(dll);
	end_node = DLLEnd(dll);
	
	state = DLLForEach(start_node, end_node, ActCount, &count);
	assert(0 == state);
	
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

dll_iter_t *DLLInsert(dll_t *dll, dll_iter_t *iter, void *data)
{  
    dll_iter_t *new_node = NULL;
	(void)dll;
	
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
	
    assert(NULL != iter->next);
    
	next_node = iter->next;
	    
    iter->prev->next = iter->next;
    iter->next->prev = iter->prev;
	
    free (iter);
    
    return (next_node);
}

dll_iter_t *DLLPushback(dll_t *dll, void *data)
{
	assert(NULL != dll);
	
	return (DLLInsert(dll, DLLEnd(dll), data));
}

dll_iter_t *DLLPushfront(dll_t *dll, void *data)
{
	assert(NULL != dll);
	
	return (DLLInsert(dll, DLLBegin(dll), data));
}

void *DLLPopback(dll_t *dll)
{
	dll_iter_t *last_node = NULL;
	void *pop_data = NULL;
	
	assert(NULL != dll);
	
	last_node = DLLEnd(dll);
	pop_data = last_node->prev->data;
	
	DLLRemove(last_node->prev);
	
	return (pop_data);
}

void *DLLPopfront(dll_t *dll)
{
	dll_iter_t *start_node = NULL;
	void *pop_data = NULL;
	
	assert(NULL != dll);
	
	start_node = DLLBegin(dll);
	pop_data = start_node->data;

	DLLRemove(start_node->next);

	return (pop_data);
}

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

int DLLForEach(dll_iter_t *from, dll_iter_t *to, action_t act_func,\
			   void *params)
{
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != act_func);
	
	while (TRUE != DLLIsEqual(from, to)) 
	{
		if (SUCCESS != act_func(from->data, params))
		{			
			return (ERROR);
		}
		from = DLLNext(from);
	}

	return (SUCCESS);
}

dll_iter_t *DLLFind(dll_iter_t *from, dll_iter_t *to, is_match_t is_match_func,\
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

void DLLSplice(dll_iter_t *from, dll_iter_t *to, dll_iter_t* where)
{
	dll_iter_t *temp_node = NULL;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != where);
	
	temp_node = where->prev;
	where->prev->next = from;
	to->prev->next = where;
	where->prev = to->prev;
	to->prev = from->prev;
	from->prev->next = to;
	from->prev = temp_node;
}

int DLLMultiFind(dll_iter_t *from, dll_iter_t *to, is_match_t is_match_func,\
				 void *params, dll_t *output)
{
	dll_iter_t *runner = NULL;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != output);
	
	runner = DLLEnd(output);
	
	while (TRUE != DLLIsEqual(from, to)) 
	{
		if (TRUE == is_match_func(from->data, params))
		{
			runner = DLLInsert(output, runner, params);
			if (NULL == runner)
			{
				return (ERROR);
			}
		}
		from = DLLNext(from);
	}
	
	return (SUCCESS);
}






















