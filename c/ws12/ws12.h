/*******************************************************************************
*Author: Arieh Farber 
*******************************************************************************/
#ifndef _WS12_
#define _WS12_

typedef struct node *node_t;

/*******************************************************************************
*Description: Reverses the order of a given slist.
*Return values: Iterator pointing to the head of the list.
*******************************************************************************/
node_t Flip(node_t head);

/*******************************************************************************
*Description: Tells whether a given slist has a loop.
*Return values: 1 - has loop
*				0 - no loop
*******************************************************************************/
int HasLoop(const node_t head);

/*******************************************************************************
*Description: compars 2 slists to see if they intersect  
*Return values: A pointer to a first node mutual to both slists, if any.
				Otherwise, returns NULL.
*******************************************************************************/
node_t FindIntersection(node_t head_1, node_t head_2);

/*******************************************************************************
*Help Functions
*******************************************************************************/
node_t CreateLinkedList(void);

node_t CreateLoopedLinkedList(void);

node_t CreateIntersectionLinkedList(void);

void DestroyLinkedList(node_t head);

void PrintList(node_t head);

#endif /*_WS12_*/
