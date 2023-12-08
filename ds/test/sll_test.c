/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Yael Argov
*Date: 06/11/2023
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

static void TstResIsEmpty(int control, int test)
{
	if (control != test)
	{
		printf("\033[1;32m");
		printf("SLL is not empty\n");
		printf("\033[0m"); 
	}
	else
	{
		printf("\033[1;32m");
		printf("SLL is empty\n");
		printf("\033[0m"); 
	}
}

static int IsMatchInt(void *control, void *test)
{
	if (*(int *)control == *(int *)test)
	{
		return (TRUE);
	}
	
	return (FALSE);
}

static int ActFuncInt(void *node_data, void *parametrs)
{
	*(int *)node_data = *(int *)parametrs;
	
	if (*(int *)node_data != *(int *)parametrs)
	{
		return (ERROR);
	}
	
	return (SUCCESS);
}

static void TestInsertAndRemove(list_t *test_list_1, int node_val_1[])
{
	slist_iter_t node_array[10];
	int i = 0;
	int remove_size = 5;
	int size = 10;
	void *get_data = NULL;
	
    for (i = 0; i < size; i++)
    {
        node_array[i] = SLLInsert(test_list_1, SLLEnd(test_list_1), &node_val_1[i]);
    }

	get_data = SLLGetData(SLLBegin(test_list_1));
	TstResInt(0, *(int *)get_data, __LINE__);
    for (i = 0; i < size - 1; i++)
    {
        get_data = SLLGetData(node_array[i]);
        TstResInt(i, *(int *)get_data, __LINE__);
    }
    
    for (i = 0; i < remove_size; i++)
    {
        node_array[i] = SLLRemove(SLLBegin(test_list_1));
    }
    
	get_data = SLLGetData(SLLBegin(test_list_1));
	TstResInt(remove_size, *(int *)get_data, __LINE__);
    for (i = remove_size + 1; i < size; i++)
    {
        get_data = SLLGetData(node_array[i]);
        TstResInt(i, *(int *)get_data, __LINE__);
    }
}

static void TestCountAndIsEmpty(list_t *test_list_1, size_t control_counter)
{
	size_t counter = 0;
	int status = 0;
		
	counter = SLLCount(test_list_1);
	TstResSizeT(control_counter, counter, __LINE__);
	
	status = SLLIsEmpty(test_list_1);
	TstResIsEmpty(status, TRUE);
}

static void TestFind(list_t *test_list_1)
{
	slist_iter_t test_from = NULL;
	slist_iter_t test_to = NULL;
	slist_iter_t test_iterator = NULL;
	slist_iter_t test_control = NULL;
	int test_params = 7;
	int i = 0;
	int status = 0;
	
	test_from = SLLBegin(test_list_1);
	test_to = SLLEnd(test_list_1);
	
	test_iterator = SLLFind(test_from, test_to, IsMatchInt, &test_params);
	
	test_control = SLLBegin(test_list_1);
    for (i = 0; i < test_params - 5; i++)
    {
    	test_control = SLLNext(test_control); 
    }
    
    status = SLLIsEqual(test_control, test_iterator);
    TstResInt(status, TRUE, __LINE__);
}

static void TestSetData(list_t *test_list_1)
{
	int data = 0;
	void *get_data = NULL;
	
	SLLSetData(SLLBegin(test_list_1), &data);
	get_data = SLLGetData(SLLBegin(test_list_1));
	TstResInt(SUCCESS, *(int *)get_data, __LINE__);
}

static void TestForEach(list_t *test_list_1)
{
	slist_iter_t test_from = NULL;
	slist_iter_t test_to = NULL;
	int test_params = 10;
	int status = 0;
	
	test_from = SLLBegin(test_list_1);
	test_to = SLLEnd(test_list_1);
	
	status = SLLForEach(test_from, test_to, ActFuncInt, &test_params);
	TstResInt(SUCCESS, status, __LINE__);
}


static void TestSLL()
{
	list_t *test_list_1 = NULL;
	list_t *test_list_2 = NULL;
	size_t control_counter1 = 0;
	size_t control_counter2 = 5;
	size_t control_counter3 = 10;
	int node_val_1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int node_val_2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	
	test_list_1 = SLLCreate();
	test_list_2 = SLLCreate();
	assert(test_list_1);
	assert(test_list_2);

	TestCountAndIsEmpty(test_list_1, control_counter1);
	
	TestInsertAndRemove(test_list_1, node_val_1);
	TestInsertAndRemove(test_list_2, node_val_2);
	
	TestFind(test_list_1);
	
	TestSetData(test_list_1);
	
	TestCountAndIsEmpty(test_list_1, control_counter2);
	
	TestForEach(test_list_1);
	
	SLLAppend(test_list_1, test_list_2);
	TestCountAndIsEmpty(test_list_1, control_counter3);
	
	SLLDestroy(test_list_1);
	SLLDestroy(test_list_2);
}























