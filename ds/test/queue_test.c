/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Eytan Peros
*Date: 09/12/2023
*******************************************************************************/
#include <stdio.h> /*printf*/

#include "sll.h"
#include "queue.h"

#define SUCCESS 0
#define TRUE 1
#define FALSE 0

static void TestQueue();

int main()
{
	TestQueue();
	
	return (0);
}

static void TestQueueEnqueueAndDequeue(queue_t *queue, int data[], int size);
static void TestQueueSize(queue_t *queue, int want_size);
static void TestQueueStatus(queue_t *queue, int want);
static void TestInt(int want, int got, int line);
void TestSizeT(size_t want, size_t got, int line);

static void TestQueue()
{
	queue_t *queue_1 = NULL;
	queue_t *queue_2 = NULL;
	int queue_val_1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int queue_val_2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int queue_size = 10;
	
	queue_1 = QueueCreate();
	queue_2 = QueueCreate();
	
	TestQueueStatus(queue_1, TRUE);
	
	TestQueueEnqueueAndDequeue(queue_1, queue_val_1, queue_size);
	TestQueueEnqueueAndDequeue(queue_2, queue_val_2, queue_size);
	
	TestQueueSize(queue_1, queue_size / 2);
	TestQueueStatus(queue_1, FALSE);
	
	QueueAppend(queue_1, queue_2);
	TestQueueSize(queue_1, queue_size);
	TestQueueStatus(queue_1, FALSE);
	
	QueueDestroy(queue_1);
	QueueDestroy(queue_2);
}

static void TestQueueEnqueueAndDequeue(queue_t *queue, int data[], int size)
{
	int status = 1;
	int i = 0;
	void *value = NULL;
	
	for (i = 0; i < size; i++)
	{
		status = QueueEnqueue(queue, &data[i]);
		value = QueuePeek(queue);
		TestInt(SUCCESS, status, __LINE__);
	}
	
	for (i = 0; i < (size / 2); i++)
	{
		QueueDequeue(queue);
		value = QueuePeek(queue);
		TestInt(i + 1, *(int *)value, __LINE__);
	}
}

static void TestQueueSize(queue_t *queue, int want_size)
{
	TestSizeT(want_size, QueueSize(queue), __LINE__);
}

static void TestQueueStatus(queue_t *queue, int want)
{
	TestInt(want, QueueIsEmpty(queue), __LINE__);
}

static void TestInt(int want, int got, int line)
{
	if (want != got)
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

void TestSizeT(size_t want, size_t got, int line)
{
	if (want != got)
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
