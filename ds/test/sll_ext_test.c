/*******************************************************************************
*Author: Arieh Farber 
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "sll_ext.h"

#define TRUE 1
#define FALSE 0

static void TestFlip();
static void TestHasLoop();
static void TestFindIntersection();

int main()
{
	TestFlip();
	TestHasLoop();
	TestFindIntersection();
	
	return (0);
}

static void TestStatusHasLoop(int want, int got);

static void TestFlip()
{
	node_t original_head = NULL;
	node_t head = NULL;

	original_head = CreateLinkedList();
    
    printf("Before flip:\n");
    PrintList(original_head);
	
	head = Flip(original_head);
	
	printf("After flip:\n");
	PrintList(head);
	printf("\n");
	
	DestroyLinkedList(head);
}

static void TestHasLoop()
{
	node_t original_head = NULL;
	int status = 0;

	original_head = CreateLoopedLinkedList();
	
	printf("Testing for loop:\n");
	status = HasLoop(original_head);
	TestStatusHasLoop(TRUE, status);
	printf("\n");
}

static void TestFindIntersection()
{
	node_t original_head = NULL;
	node_t intersection_head = NULL;
	node_t intersection_node = NULL;

	original_head = CreateLinkedList();
	intersection_head = CreateIntersectionLinkedList();
    
    printf("Original lists:\n");
    PrintList(original_head);
    PrintList(intersection_head);
	
	intersection_node = FindIntersection(original_head, intersection_head);
	assert(intersection_node);
	
	printf("List from intersection:\n");
	PrintList(intersection_node);
	
	DestroyLinkedList(original_head);
}

static void TestStatusHasLoop(int want, int got)
{
	if (want != got)
	{
		printf("\033[0;32m");
		printf("No loop!\n");
		printf("\033[0m"); 
	}
	else
	{
		printf("\033[0;32m");
		printf("Has loop!\n");
		printf("\033[0m"); 
	}
}
