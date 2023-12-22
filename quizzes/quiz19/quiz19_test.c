/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Yael Argov
*Date: 06/11/2023
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <assert.h> /*assert*/

#include "quiz19.h"

#define ERROR -1
#define SUCCESS 0
#define TRUE 1
#define FALSE 0

static void TestSLL();

int main()
{
	TestSLL();
	
	return (0);
}

static void TestInsert(list_t *list, int node_val[])
{
	slist_iter_t node_array[10];
	int i = 0;
	int size = 10;
	
    for (i = 0; i < size; i++)
    {
        node_array[i] = SLLInsert(list, SLLEnd(list), &node_val[i]);
    }
    
    (void)node_array;
}

static void TestFindNthElement(list_t *list, int n)
{
	slist_iter_t runner = SLLBegin(list);
	slist_iter_t diff_runner = SLLBegin(list);
	int i = 0;
	
	for (i = 0; i < n; i++)
	{
		diff_runner = SLLNext(diff_runner);
	}
	
	while (TRUE != SLLIsEqual(diff_runner, SLLEnd(list)))
	{
		runner = SLLNext(runner);
		diff_runner = SLLNext(diff_runner);
	} 
	
	printf("Nth data:%d\n", *(int *)SLLGetData(runner));
}


static void TestSLL()
{
	list_t *list = NULL;
	int node_val[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int n = 3;
	
	list = SLLCreate();
	assert(list);
	
	TestInsert(list, node_val);
	
	TestFindNthElement(list, n);
	
	SLLDestroy(list);
}























