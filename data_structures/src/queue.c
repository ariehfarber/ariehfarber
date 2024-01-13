/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Eytan Peros
*Date: 09/12/2023
*******************************************************************************/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/

#include "queue.h"
#include "sll.h"
#include "ds_utils.h" 

#define ERROR -1

struct queue
{
	list_t *list;
};

queue_t *QueueCreate(void)
{
	queue_t *queue = NULL;
	
	queue = (queue_t *)malloc(sizeof(struct queue));
	
	queue->list = SLLCreate();

	return (queue);
}

void QueueDestroy(queue_t *queue)
{
	assert(NULL != queue);
	
	SLLDestroy(queue->list);
	
	free(queue);
}

int QueueEnqueue(queue_t *queue, const void *val)
{	
	assert(NULL != queue);
	
	return (NULL == SLLInsert(queue->list, SLLEnd(queue->list), (void *)val));
}

void QueueDequeue(queue_t *queue)
{
	assert(NULL != queue);

	SLLRemove(SLLBegin(queue->list));
}

void *QueuePeek(const queue_t *queue)
{
	assert(NULL != queue);
	
	return (SLLGetData(SLLBegin(queue->list)));
}

size_t QueueSize(const queue_t *queue)
{
	assert(NULL != queue);
	
	return (SLLCount(queue->list));
}

int QueueIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);

	return (SLLIsEmpty(queue->list));
}

void QueueAppend(queue_t *dest, queue_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	SLLAppend(dest->list, src->list);
}
