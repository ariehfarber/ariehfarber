/*******************************************************************************
*Date: 03/12/2023
*******************************************************************************/
#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h> /*size_t*/

typedef struct stack stack_t;

/******************************************************************************
*Description: Creates a new stack.
*Parameters: Capacity of the stack and the size of the elements.
*Return Value: Pointer to the stack.
*Time Complexity: O(1).
*Space Complexity: O(n).
*Notes: Capacity or element size 0 will resault in undefined behavior.
*		If the memory allocation failes, returns NULL.
******************************************************************************/
stack_t *StackCreate(size_t capacity, size_t element_size);

/******************************************************************************
*Description: Destroys the given stack.
*Parameters: Pointer to the stack.
*Return Value: Void.
*Time Complexity: O(1).
*Space Complexity: O(1).
******************************************************************************/
void StackDestroy(stack_t *stack);

/******************************************************************************
*Description: Pushes the given data to the top of the stack.
*Parameters: Pointer to the stack and the data to be pushed.
*Return Value: Void.
*Time Complexity: O(1).
*Space Complexity: O(1).
*Notes: Pushing to a full stack will resault in undefined behavior.
******************************************************************************/
void StackPush(stack_t *stack, const void *data);

/******************************************************************************
*Description: Pops the top of the stack out.
*Parameters: Pointer to the stack.
*Return Value: Void.
*Time Complexity: O(1).
*Space Complexity: O(1).
*Notes: Popping out of an empty stack will resault in undefined behavior.
******************************************************************************/
void StackPop(stack_t *stack);

/******************************************************************************
*Description: Returns the data at the top of the stack.
*Parameters: Pointer to the stack.
*Return Value: The data at the top of the stack.
*Time Complexity: O(1).
*Space Complexity: O(1).
*Notes: Peeking into an empty stack will resault in undefined behavior.
******************************************************************************/
void *StackPeek(const stack_t *stack);

/******************************************************************************
*Description: Checks whether the stack is empty or not
*Parameters: Pointer to the stack.
*Return Value: Boolean, TRUE if the stack is empty and FALSE otherwise.
*Time Complexity: O(1).
*Space Complexity: O(1).
******************************************************************************/
int StackIsEmpty(const stack_t *stack);

/******************************************************************************
*Description: Returns the current size of the stack.
*Parameters: Pointer to the stack.
*Return Value: The current size of the stack.
*Time Complexity: O(1).
*Space Complexity: O(1).
******************************************************************************/
size_t StackSize(const stack_t *stack);

/******************************************************************************
*Description: Returns the capacity of the stack.
*Parameters: Pointer to the stack.
*Return Value: The capacity of the stack.
*Time Complexity: O(1).
*Space Complexity: O(1).
******************************************************************************/
size_t StackCapacity(const stack_t *stack);

#endif	/*__STACK_H__*/
