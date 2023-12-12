/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Yael Argov
*Date: 06/11/2023
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
	slist_iter_t next;
};

struct list
{
	slist_iter_t head;
	slist_iter_t tail;
};

list_t *SLLCreate(void)
{
	slist_iter_t dummy_node = NULL;
	 
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
	slist_iter_t current = NULL;

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
    slist_iter_t new_node = NULL;

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
    
    return (iterator);
}

slist_iter_t SLLRemove(slist_iter_t iterator)
{	
	slist_iter_t temp_node = NULL;
	
	assert(NULL != iterator);
	assert(NULL != iterator->next);
	
	temp_node = iterator->next;
	iterator->data = temp_node->data;
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
	size_t count = 0;
	slist_iter_t runner = NULL;
	slist_iter_t end_node = NULL;

	assert(NULL != list);

	runner = SLLBegin(list);
	end_node = SLLEnd(list);

	while (TRUE != SLLIsEqual(runner, end_node)) 
	{
		runner = SLLNext(runner);
		count++;
	}
	
	return (count);
}

slist_iter_t SLLFind(slist_iter_t from, slist_iter_t to,
		   			 is_match_t is_match_func, void *params)
{
	assert(NULL != from);
	assert(NULL != to);
	
	while (TRUE != SLLIsEqual(from, to)) 
	{
		if (TRUE ==is_match_func(from->data, params))
		{
			return (from);
		}
		from = SLLNext(from);
	}
	
	return (NULL);
}

int SLLIsEmpty(const list_t *list)
{
	return (TRUE == SLLIsEqual(SLLBegin(list), SLLEnd(list)));
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

	return (iterator_1 == iterator_2);
}

int SLLForEach(slist_iter_t from, slist_iter_t to, action_t act_func,
			   void *params)
{
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != act_func);
		
	while (TRUE != SLLIsEqual(from, to)) 
	{
		if (act_func(from->data, params) != SUCCESS)
		{			
			return (ERROR);
		}
		from = SLLNext(from);
	}
	
	return (SUCCESS);
}

void SLLAppend(list_t *dest, list_t *src)
{
	slist_iter_t dest_end_node = NULL;
	slist_iter_t src_start_node = NULL;
	
	if (src->tail == src->head)
	{
		return;
	}
	
	dest_end_node = SLLEnd(dest);
	src_start_node = SLLBegin(src);
	
	dest_end_node->data = src_start_node->data;
	dest_end_node->next = src_start_node->next;
	
	src_start_node->data = NULL;
	src_start_node->next = NULL;
	
	dest->tail = src->tail;
	src->tail = src->head;
	
	dest->tail->data = dest;
	src->tail->data = src;
}










