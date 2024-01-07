/*******************************************************************************
*Date: 21/12/2023
*******************************************************************************/
#ifndef __PQ_H__
#define __PQ_H__

#include <stddef.h> /* size_t */

typedef struct pq pq_t;
typedef int (*pq_is_match_t)(void *,void *);
typedef int (*pq_compare_t)(void *,void *);

/*******************************************************************************
*Description: Creates new priority queue.
*Parameters: A comparison function:
*			 if comp(data1, data2) > 0: the queue ordering is data2 ->..-> data1
*			 if comp(data1, data2) == 0: the data is considered equal 
*			 if comp(data1, data2) < 0: the queue ordering is data1 ->..->data2
*Return Value: Pointer to the created priority queue.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Returns NULL if memory allocation fails.
*******************************************************************************/
pq_t *PQCreate(pq_compare_t compare_func);

/*******************************************************************************
*Description: Deletes the entire priority queue.
*Parameters: Pointer to a priority queue.
*Time Complexity: O(n)
*Space Complexity: O(1)
*******************************************************************************/
void PQDestroy(pq_t *pq);

/*******************************************************************************
*Description: Checks whether the given priority queue is empty.
*Parameters: Pointer to a priority queue.
*Return Value: 1 if the priority queue is empty, 0 otherwise.
*Time Complexity: O(1)
*Space Complexity: O(1)
*******************************************************************************/
int PQIsEmpty(const pq_t *pq);

/*******************************************************************************
*Description: Returns the amount of elements in the given priority queue.
*Parameters: Pointer to a priority queue.
*Time Complexity: O(n)
*Space Complexity: O(1)
*******************************************************************************/
size_t PQSize(const pq_t *pq);

/*******************************************************************************
*Description: Creates a new element with the given data, and inserts it into the
*			  priority queue.
*Parameters: Data to insert, and a pointer to a priority queue.
*Return Value: 0 for success.
*              -1 for error.
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: If memory allocation fails return a non-zero FAIL status.
*******************************************************************************/
int PQEnqueue(pq_t *pq, void *data);

/*******************************************************************************
*Description: Removes the element with the highest priority from the queue.
*Parameters: Pointer to a priority queue.
*Return Value: Pointer to the removed element data.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Calling the function on an empty queue will lead to undefined behavior.
*******************************************************************************/
void *PQDequeue(pq_t *pq);

/*******************************************************************************
*Description: Gets data from the top of the priority queue.
*Parameters: Pointer to a priority queue.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Calling the function on an empty queue will lead to undefined behavior.
*******************************************************************************/
void *PQPeek(const pq_t *pq);

/*******************************************************************************
*Description: Deletes all the elements in the priority queue.
*Parameters: Pointer to a priority queue.
*Time Complexity: O(n)
*Space Complexity: O(1)
*******************************************************************************/
void PQClear(pq_t *pq);

/*******************************************************************************
*Description: Delete the first matching element in the priority queue.
*Parameters:  Pointer to a priority queue.
*             An isMatch function: 1 - clear this element.
*                                  0 - no match.
*             Pointer to params for isMatch function.
*Return Value: Return pointer to the deleted data, NULL if no match is found.
*Time Complexity: O(n)
*Space Complexity: O(1)
*******************************************************************************/
void *PQErase(pq_t *pq, pq_is_match_t is_match_func, void *params);

#endif /*__PQ_H__*/
