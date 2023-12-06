/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#ifndef __SLL_H__
#define __SLL_H__

#include <stddef.h> /*size_t*/

typedef struct node *slist_iter_t;
typedef struct list list_t;
typedef int (*is_match_t)(void *, void *);
typedef int (*action_t)(void *, void *);

/******************************************************************************
*Description: Creates a new list.
*Arguments: None.
*Return Value: Pointer to the created list.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: If memory allocation fails, return NULL.
******************************************************************************/
list_t* SLLCreate(void);

/******************************************************************************
*Description: Deletes the entire list.
*Arguments: Pointer to a list.
*Return Value: Void.
*Time Complexity: O(n)
*Space Complexity: O(1)
******************************************************************************/
void SLLDestroy(list_t *list);

/******************************************************************************
*Description: Creates a new node with the given data, and inserts it before
*			  the given iterator.
*Arguments: Pointer to the list, an iterator that points to the insertion 
*			location and data to insert.
*Return Value: Iterator pointing to the inserted node.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: The given iterator "where" becomes invalidated after use.
*		If memory allocation fails, returns NULL
******************************************************************************/
slist_iter_t SLLInsert(list_t *list, slist_iter_t iterator, void *value);

/******************************************************************************
*Description: Removes the given iterator from the list.
*Arguments: Iterator to be removed from the list.
*Return Value: Iterator that points to the next node.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Sending the end of the list as an argument will result in 
*		undefined behavior.
******************************************************************************/
slist_iter_t SLLRemove(slist_iter_t iterator);

/******************************************************************************
*Description: Counts the number of nodes in a given list.
*Arguments: Pointer to a list.
*Return Value: The number of nodes.
*Time Complexity: O(n)
*Space Complexity: O(1)
******************************************************************************/
size_t SLLCount(const list_t *list);

/******************************************************************************
*Description: Finds a node with specific data in the given range. starting at
*             iterator "from" (inclusive) until iterator "to" (non-inclusive).
*Arguments: 2 iterators that mark the range, a comparison function,
*           and parameters to compare.
*Return Value: Iterator pointing to the node with matching data.
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: Returns NULL if no match was found.
* 		sending "to" that comes before "from" as parameters will result in 
*		undefined behavior.
******************************************************************************/
slist_iter_t SLLFind(slist_iter_t from, slist_iter_t to,
				is_match_t is_match_func, void *params);

/******************************************************************************
*Description: Checks whether the given list is empty.
*Arguments: Pointer to a list
*Return Value: 1 if the list is empty, or 0 otherwise.
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
int SLLIsEmpty(const list_t *list);

/******************************************************************************
*Description: Updates the iterator to point to the end of the list.
*Arguments: Pointer to a list.
*Return Value: Iterator that points to the end of the list.
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
slist_iter_t SLLEnd(const list_t *list);

/******************************************************************************
*Description: Updates the iterator to point to the beginning of the list.
*Arguments: Pointer to a list.
*Return Value: Iterator that points to the beginning of the list.
*Time Complexity: O(1)
*Space Complexity: O(1) 
******************************************************************************/
slist_iter_t SLLBegin(const list_t *list);

/******************************************************************************
*Description: Advances the iterator to the next node.
*Arguments: Iterator.
*Return Value: Iterator that points to the next node.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Inputting the end of a list will result in undefined behavior.
******************************************************************************/
slist_iter_t SLLNext(slist_iter_t iterator); 

/******************************************************************************
*Description: Gets the data pointed to by the iterator.
*Arguments: Iterator.
*Return Value: The data pointed to.
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
void *SLLGetData(slist_iter_t iterator);

/******************************************************************************
*Description: Sets data in the given iterator.
*Arguments: Iterator and pointer to the data.
*Return Value: Void
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Inputting the end of a list will result in undefined behavior.
******************************************************************************/
void SLLSetData(slist_iter_t iterator, void *data);

/******************************************************************************
*Description: Checks whether 2 iterators point to the same node.
*Arguments: 2 iterators to compare.
*Return Value: 1 if they point to the same node, and 0 otherwise.
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
int SLLIsEqual(slist_iter_t iterator_1, slist_iter_t iterator_2);

/******************************************************************************
*Description: Iterates over the given range, starting at iterator 
*			  "from" (inclusive) until iterator "to" (non-inclusive),
*			  and acts on the data.
*Arguments: 2 iterators that mark the range, an operation function,
*			and additional parameters.
*Return Value: 0 if the action was successfull, and -1 otherwise
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: sending "to" that comes before "from" as parameters will result in 
*		undefined behavior.
******************************************************************************/
int SLLForEach(slist_iter_t from, slist_iter_t to, action_t act_func, void *params);

#endif /* __SLL_H__ */
