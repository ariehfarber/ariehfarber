/*******************************************************************************
*Author: Arieh Farber 
*******************************************************************************/
#include <stddef.h> /*NULL  */
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc*/
#include <stdio.h>  /*printf*/

#include "sll_ext.h"

struct node
{
    void *data;
    node_t next;
};

static node_t head;
static node_t node1;
static node_t node2;
static node_t node3;
static node_t node4;

static void DestroyLoop(node_t slow, node_t fast, node_t head);
static void DestroyIntersection(node_t head, node_t runner);
node_t CreateLinkedList(void);
node_t CreateLoopedLinkedList(void);
node_t CreateIntersectionLinkedList(void);
void DestroyLinkedList(node_t head);
void PrintList(node_t head);

node_t Flip(node_t head)
{
    node_t prev = NULL;
    node_t current = NULL;
    node_t next = NULL;
    
	assert(NULL != head);
    
    current = head;
    
    while (NULL != current) 
    {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
    }
    
    head = prev;
    
    return (head);
}

int HasLoop(const node_t head)
{
    node_t slow = NULL;
    node_t fast = NULL;
    int status = 0;

	assert(NULL != head);
	
	slow = head;
	fast = head;
	
    while (slow != NULL) 
    {
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
		{
			status = 1;
			DestroyLoop(slow, fast, head);
			break;
		}
    }
    
    return (status);
}

node_t FindIntersection(node_t head_1, node_t head_2)
{
	node_t runner_1 = NULL;
	size_t counter_1 = 0;
    node_t runner_2 = NULL;
    size_t counter_2 = 0;
    size_t diff = 0;
    
    assert(NULL != head_1);
    assert(NULL != head_2);
    
    runner_1 = head_1;
    runner_2 = head_2;
    
    while (NULL != runner_1)
    {
    	runner_1 = runner_1->next;
    	counter_1++;
    }
    
    while (NULL != runner_2)
    {
    	runner_2 = runner_2->next;
    	counter_2++;
    }
    
    runner_1 = head_1;
    runner_2 = head_2;
    diff = counter_2 - counter_1;
    
    if (0 < diff)
    {
    	while (0 != diff)
    	{
    		runner_2 = runner_2->next;
    		diff--;
    	}
    }
    else
    {
    	while (0 != diff)
    	{
    		runner_1 = runner_1->next;
    		diff--;
    	}
    }
    
    while (NULL != runner_1)
	{
		if (runner_1 == runner_2)
		{
			DestroyIntersection(head_2, runner_2);
			return (runner_1);
		}
		runner_1 = runner_1->next;
		runner_2 = runner_2->next;
	}
    
    return (NULL);    
}

node_t CreateLinkedList(void)
{
    static int head_val = 0;
    static int node1_val = 1;
    static int node2_val = 2;
	static int node3_val = 3;
    static int node4_val = 4;
    
    head = (node_t)malloc(sizeof(struct node));
    node1 = (node_t)malloc(sizeof(struct node));
    node2 = (node_t)malloc(sizeof(struct node));
    node3 = (node_t)malloc(sizeof(struct node));
    node4 = (node_t)malloc(sizeof(struct node));
    
    head->data = &head_val;
    head->next = node1;
    node1->data = &node1_val;
    node1->next = node2;
    node2->data = &node2_val;
    node2->next = node3;
    node3->data = &node3_val;
    node3->next = node4;
    node4->data = &node4_val;
    node4->next = NULL;
    
	return (head);
}

node_t CreateLoopedLinkedList(void)
{
    static int head_val = 0;
    static int node1_val = 1;
    static int node2_val = 2;
	static int node3_val = 3;
    static int node4_val = 4;
    
    head = (node_t)malloc(sizeof(struct node));
    node1 = (node_t)malloc(sizeof(struct node));
    node2 = (node_t)malloc(sizeof(struct node));
    node3 = (node_t)malloc(sizeof(struct node));
    node4 = (node_t)malloc(sizeof(struct node));
    
    head->data = &head_val;
    head->next = node1;
    node1->data = &node1_val;
    node1->next = node2;
    node2->data = &node2_val;
    node2->next = node3;
    node3->data = &node3_val;
    node3->next = node4;
    node4->data = &node4_val;
    node4->next = node1;
    
	return (head);
}

node_t CreateIntersectionLinkedList(void)
{
	static node_t intersection_head = NULL;
    static node_t nodeA = NULL;
    static node_t nodeB = NULL;

    static int head_val = 10;
    static int nodeA_val = 11;
    static int nodeB_val = 12;

    intersection_head = (node_t)malloc(sizeof(struct node));
    nodeA = (node_t)malloc(sizeof(struct node));
    nodeB = (node_t)malloc(sizeof(struct node));

    intersection_head->data = &head_val;
    intersection_head->next = nodeA;
    nodeA->data = &nodeA_val;
    nodeA->next = nodeB;
    nodeB->data = &nodeB_val;
    nodeB->next = node2;
    
	return (intersection_head);
}

void DestroyLinkedList(node_t head)
{
	node_t temp = NULL;

	assert(NULL != head);

	temp = head;

	while (head != NULL) 
	{
		temp = head;
		head = head->next; 
		free(temp);       
	}
}

void PrintList(node_t head)
{
    node_t temp = NULL;
    
    temp = head;
    
    while (NULL != temp) 
    {
        printf("%d ", *(int *)temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void DestroyLoop(node_t slow, node_t fast, node_t head)
{
    assert(NULL != slow); 
    assert(NULL != fast);
    assert(NULL != head);
    
    slow = head;
    
    while (slow != fast) 
    {
        slow = slow->next;
        fast = fast->next;
    }

    while (fast->next != slow) 
    {
        fast = fast->next;
    }

    fast->next = NULL;
    
	DestroyLinkedList(head);
}

void DestroyIntersection(node_t head, node_t runner)
{
	node_t temp = NULL;

	assert(NULL != head);

	temp = head;

	while (head != runner) 
	{
		temp = head;
		head = head->next; 
		free(temp);       
	}
}
