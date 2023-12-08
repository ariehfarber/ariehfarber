/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stdio.h> /*printf*/

#include "sll.h"
#include "queue.h"

#define ERROR -1
#define SUCCESS 0
#define TRUE 1
#define FALSE 0

static void TestQueue();

int main()
{
	TestQueue();
	
	return (0);
}

static void TstResInt(int control, int test, int line)
{
	if (control != test)
	{
		printf("\033[0;31m");
		printf("Error. failed at line %d\n", line);
		printf("\033[0m"); 
	}
	else
	{
		printf("\033[1;32m");
		printf("Success!\n");
		printf("\033[0m"); 
	}
}

static void TstResSizeT(size_t control, size_t func_res, int line)
{
	if (control != func_res)
	{
		printf("\033[0;31m");
		printf("Error. failed at line %d\n", line);
		printf("\033[0m"); 
	}
	else
	{
		printf("\033[1;32m");
		printf("Success!\n");
		printf("\033[0m"); 
	}
}

static void TestQueueEnqueueAndDequeue(queue_t *queue, int data[], int size)
{
	int status = 1;
	int i = 0;
	void *value = NULL;
	
	for (i = 0; i < size; i++)
	{
		status = QueueEnqueue(queue, &data[i]);
		TstResInt(SUCCESS, status, __LINE__);
	}
	
	for (i = 0; i < (size / 2); i++)
	{
		QueueDequeue(queue);
		value = QueuePeek(queue);
		TstResInt(8 - i, *(int *)value, __LINE__);
	}
}

static void TestQueueSize(queue_t *queue, int control_size)
{
	TstResSizeT(control_size, QueueSize(queue), __LINE__);
}

static void TestQueueStatus(queue_t *queue, int control)
{
	TstResInt(control, QueueIsEmpty(queue), __LINE__);
}

static void TestQueue()
{
	queue_t *queue = NULL;
	int queue_val[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int queue_size = 10;
	
	queue = QueueCreate();
	
	TestQueueStatus(queue, TRUE);
	
	TestQueueEnqueueAndDequeue(queue, queue_val, queue_size);
	
	TestQueueSize(queue, queue_size / 2);
	
	TestQueueStatus(queue, FALSE);
	
	QueueDestroy(queue);
}














