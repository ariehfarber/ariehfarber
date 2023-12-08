/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/

#include "sll.h"
#include "queue.h"

#define SUCCESS 0
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
	assert(queue);
	
	SLLDestroy(queue->list);
	
	free(queue);
}

int QueueEnqueue(queue_t *queue, const void *val)
{	
	assert(queue);
	
	return (NULL == SLLInsert(queue->list, SLLBegin(queue->list), (void *)val));
}

void QueueDequeue(queue_t *queue)
{
	assert(queue);

	SLLRemove(SLLBegin(queue->list));
}

void *QueuePeek(const queue_t *queue)
{
	assert(queue);
	
	return (SLLGetData(SLLBegin(queue->list)));
}

size_t QueueSize(const queue_t *queue)
{
	assert(queue);
	
	return (SLLCount(queue->list));
}

int QueueIsEmpty(const queue_t *queue)
{
	assert(queue);

	return (SLLIsEmpty(queue->list));
}














