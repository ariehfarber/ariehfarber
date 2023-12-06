/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <assert.h> /*assert	  */
#include <stdlib.h> /*malloc, free*/

#include "sll.h"

#define ERROR -1
#define SUCCESS 0
#define TRUE 1

struct node
{
	void *data;
	struct node *next;
};

struct list
{
	struct node *head;
	struct node *tail;
};

list_t *SLLCreate(void)
{
	slist_iter_t dummy_node;
	 
	list_t *list = (list_t *)malloc(sizeof(list_t));
    if (NULL == list) 
    {
        return (NULL);
    }
    
    dummy_node = (slist_iter_t)malloc(sizeof(struct node));
    if (NULL == dummy_node) 
    {
        free(list);
        return (NULL);
    }
    
    dummy_node->data = list;
    dummy_node->next = NULL;
    
    list->head = dummy_node;
    list->tail = dummy_node;
	
	return (list);	
}

void SLLDestroy(list_t *list)
{
	slist_iter_t current;

	assert(NULL != list);

	current = SLLBegin(list);

	while (current != SLLEnd(list)) 
	{
		current = SLLRemove(current);
	}

	free(current);
	free(list);
}

slist_iter_t SLLInsert(list_t *list, slist_iter_t iterator, void *value)
{
    slist_iter_t new_node;

    assert(NULL != list);
    assert(NULL != iterator);

    new_node = (slist_iter_t)malloc(sizeof(struct node));
    if (NULL == new_node)
    {
        return (NULL);
    }

    new_node->data = iterator->data;
    new_node->next = iterator->next;
    iterator->data = value;
    iterator->next = new_node;    

    
	if (SLLIsEqual(iterator, list->tail))
    {
        list->tail = new_node;
    }
    
    return (new_node);
}

slist_iter_t SLLRemove(slist_iter_t iterator)
{	
	slist_iter_t temp_node;
	
	assert(NULL != iterator);
	assert(NULL != iterator->next);
	
	temp_node = iterator->next;
	iterator->data = iterator->next->data;
	iterator->next = temp_node->next;
	
	if (NULL == temp_node->next)
	{	
		((list_t *)(iterator->data))->tail = iterator;
	}
	
	free(temp_node);

	return (iterator);
}

size_t SLLCount(const list_t *list)
{
	size_t counter = 0;
	slist_iter_t runner;

	assert(NULL != list);

	runner = SLLBegin(list);

	while (runner != SLLEnd(list)) 
	{
		runner = SLLNext(runner);
		counter++;
	}
	
	return (counter);
}

slist_iter_t SLLFind(slist_iter_t from, slist_iter_t to,
		   			 is_match_t is_match_func, void *params)
{
	assert(NULL != from);
	assert(NULL != to);
	
	if (is_match_func(from->data, params) == TRUE)
	{			
		return (from);
	}
	
	while (from->next != to->next)
	{
		if (is_match_func(from->data, params) == TRUE)
		{
			return (from);
		}
		from = SLLNext(from);
		
		if (NULL == from->next)
		{
			break;
		}
	}
	
	return (NULL);
}

int SLLIsEmpty(const list_t *list)
{
	return (0 == SLLCount(list));
}

slist_iter_t SLLEnd(const list_t *list)
{
	assert(NULL != list);
	
	return (list->tail);
}

slist_iter_t SLLBegin(const list_t *list)
{
	assert(NULL != list);
	
	return (list->head);
}

slist_iter_t SLLNext(slist_iter_t iterator)
{
	assert(NULL != iterator->next);
	
	return (iterator->next);
}

void *SLLGetData(slist_iter_t iterator)
{
	assert(NULL != iterator->next);
	
	return (iterator->data);
}

void SLLSetData(slist_iter_t iterator, void *data)
{
	assert(NULL != iterator);
	
	iterator->data = data;
}

int SLLIsEqual(slist_iter_t iterator_1, slist_iter_t iterator_2)
{
	assert(NULL != iterator_1);
	assert(NULL != iterator_2);

	return (iterator_1->next == iterator_2->next);
}

int SLLForEach(slist_iter_t from, slist_iter_t to, action_t act_func,
			   void *params)
{
	assert(NULL != from);
	assert(NULL != to);
	
	if (act_func(from->data, params) != SUCCESS)
	{			
		return (ERROR);
	}
	
	
	while (from->next != to->next)
	{
		if (act_func(from->data, params) != SUCCESS)
		{			
			return (ERROR);
		}
		from = SLLNext(from);
	}
	
	return (SUCCESS);
}
