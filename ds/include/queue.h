/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Eytan Peros
*Date: 09/12/2023
*******************************************************************************/
#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h> /*size_t*/

typedef struct queue queue_t;

/******************************************************************************
*Description: Creates a new queue.
*Parameters: None.
*Return Value: Pointer to the created queue.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Returns NULL if memory allocation failed.
******************************************************************************/
queue_t *QueueCreate(void);

/******************************************************************************
*Description: Destroys the given queue.
*Parameters: Pointer to a queue to destroy.
*Return Value: None.
*Time Complexity: O(n)
*Space Complexity: O(1)
******************************************************************************/
void QueueDestroy(queue_t *queue);

/******************************************************************************
*Description: Adds a new element to the back of the queue.
*Parameters: Pointer to the queue and pointer to data to enqueue.
*Return Value: 0 in case of success, and none-zero value otherwise.
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
int QueueEnqueue(queue_t *queue, const void *data);

/******************************************************************************
*Description: Removes the element at the front of the queue.
*Parameters: Pointer to the queue.
*Return Value: None.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: undefined behavior if the queue is empty.
******************************************************************************/
void QueueDequeue(queue_t *queue);

/******************************************************************************
*Description: Returns the data of the front element of the queue.
*Parameters: Pointer to the queue.
*Return Value: Data of the front element.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Undefined behavior if the queue is empty.
******************************************************************************/
void *QueuePeek(const queue_t *queue);

/******************************************************************************
*Description: Counts the number of elements in the queue.
*Parameters: Pointer to the queue.
*Return Value: The number of elements.
*Time Complexity: O(n)
*Space Complexity: O(1)
******************************************************************************/
size_t QueueSize(const queue_t *queue);

/******************************************************************************
*Description: Checks whether the given queue is empty.
*Parameters: Pointer to the queue.
*Return Value: 1 if the queue is empty, and 0 otherwise.
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
int QueueIsEmpty(const queue_t *queue);

/******************************************************************************
*Description: Appends the queue "src" to the back of the queue "dest"
*			  and empties "src".
*Parameters: Two pointers to queues to append to each other.
*Return Value: None.
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
void QueueAppend(queue_t *dest, queue_t *src);

#endif /*__QUEUE_H__*/
