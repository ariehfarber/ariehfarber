/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <assert.h> /*assert*/

#include "sll.h"

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

static void TstResSizeT(size_t control, size_t test, int line)
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

/*static int IsMatch(void *control, void *test)*/
/*{*/
/*	if (*(int *)control == *(int *)test)*/
/*	{*/
/*		return (TRUE);*/
/*	}*/
/*	*/
/*	return (FALSE);*/
/*}*/

/*static int ActFunc(void *node_data, void *parametrs)*/
/*{*/
/*	*(int *)node_data = *(int *)parametrs;*/
/*	*/
/*	if (*(int *)node_data != *(int *)parametrs)*/
/*	{*/
/*		return (ERROR);*/
/*	}*/
/*	*/
/*	return (SUCCESS);*/
/*}*/

static void TestSLL()
{
	list_t *test_list;
	slist_iter_t node_array[10];
	int i = 0;
	int j = 5;
	int size = 10;
	int node_val[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	void *get_data = NULL;
	size_t counter = 0;
	
	test_list = SLLCreate();
	assert(test_list);
	
	counter = SLLCount(test_list);
	TstResSizeT(0, counter, __LINE__);
	
    for (i = 0; i < size; i++)
    {
        node_array[i] = SLLInsert(test_list, SLLEnd(test_list), &node_val[i]);
    }
    
    counter = SLLCount(test_list);
	TstResSizeT(10, counter, __LINE__);
	
	get_data = SLLGetData(SLLBegin(test_list));
	TstResInt(0, *(int *)get_data, __LINE__);
    for (i = 0; i < size - 1; i++)
    {
        get_data = SLLGetData(node_array[i]);
        TstResInt(i + 1, *(int *)get_data, __LINE__);
    }
    
    for (i = 0; i < j; i++)
    {
        node_array[i] = SLLRemove(SLLBegin(test_list));
    }
    
    counter = SLLCount(test_list);
	TstResSizeT(5, counter, __LINE__);
    
	get_data = SLLGetData(SLLBegin(test_list));
	TstResInt(j, *(int *)get_data, __LINE__);
    for (i = j; i < size - 1; i++)
    {
        get_data = SLLGetData(node_array[i]);
        TstResInt(i + 1, *(int *)get_data, __LINE__);
    }
	
	SLLDestroy(test_list);
}























