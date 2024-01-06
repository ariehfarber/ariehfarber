/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Yael Argov
*Date: 06/11/2023
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <assert.h> /*assert*/

#include "sll.h"
#include "ds_utils.h" /*TRUE, FALSE, SUCCESS, TestInt, TestSizeT*/

#define ERROR -1

static void TestSLL();

int main()
{
	TestSLL();
	
	return (0);
}

static void TestInsertAndRemove(list_t *got_list_1, int node_val_1[]);
static void TestCountAndIsEmpty(list_t *got_list_1, size_t want_counter);
static void TestFind(list_t *got_list_1);
static void TestSetData(list_t *got_list_1);
static void TestForEach(list_t *got_list_1);
static int IsMatchInt(void *want, void *got);
static int ActFuncInt(void *node_data, void *parametrs);
static void TestIsEmpty(int want, int got);

static void TestSLL()
{
	list_t *got_list_1 = NULL;
	list_t *got_list_2 = NULL;
	size_t want_counter1 = 0;
	size_t want_counter2 = 5;
	size_t want_counter3 = 10;
	int node_val_1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int node_val_2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	
	got_list_1 = SLLCreate();
	got_list_2 = SLLCreate();
	assert(got_list_1);
	assert(got_list_2);

	TestCountAndIsEmpty(got_list_1, want_counter1);
	
	TestInsertAndRemove(got_list_1, node_val_1);
	TestInsertAndRemove(got_list_2, node_val_2);
	
	TestFind(got_list_1);
	
	TestSetData(got_list_1);
	
	TestCountAndIsEmpty(got_list_1, want_counter2);
	
	TestForEach(got_list_1);
	
	SLLAppend(got_list_1, got_list_2);
	TestCountAndIsEmpty(got_list_1, want_counter3);
	
	SLLDestroy(got_list_1);
	SLLDestroy(got_list_2);
}

static void TestInsertAndRemove(list_t *got_list_1, int node_val_1[])
{
	slist_iter_t node_array[10];
	int i = 0;
	int remove_size = 5;
	int size = 10;
	void *get_data = NULL;
	
    for (i = 0; i < size; i++)
    {
        node_array[i] = SLLInsert(got_list_1, SLLEnd(got_list_1), &node_val_1[i]);
    }

	get_data = SLLGetData(SLLBegin(got_list_1));
	TestInt(0, *(int *)get_data, __LINE__);
    for (i = 0; i < size - 1; i++)
    {
        get_data = SLLGetData(node_array[i]);
        TestInt(i, *(int *)get_data, __LINE__);
    }
    
    for (i = 0; i < remove_size; i++)
    {
        node_array[i] = SLLRemove(SLLBegin(got_list_1));
    }
    
	get_data = SLLGetData(SLLBegin(got_list_1));
	TestInt(remove_size, *(int *)get_data, __LINE__);
    for (i = remove_size + 1; i < size; i++)
    {
        get_data = SLLGetData(node_array[i]);
        TestInt(i, *(int *)get_data, __LINE__);
    }
}

static void TestCountAndIsEmpty(list_t *got_list_1, size_t want_counter)
{
	size_t counter = 0;
	int status = 0;
		
	counter = SLLCount(got_list_1);
	TestSizeT(want_counter, counter, __LINE__);
	
	status = SLLIsEmpty(got_list_1);
	TestIsEmpty(status, TRUE);
}

static void TestFind(list_t *got_list_1)
{
	slist_iter_t got_from = NULL;
	slist_iter_t got_to = NULL;
	slist_iter_t got_iterator = NULL;
	slist_iter_t got_want = NULL;
	int got_params = 7;
	int i = 0;
	int status = 0;
	
	assert(NULL != got_list_1);
	
	got_from = SLLBegin(got_list_1);
	got_to = SLLEnd(got_list_1);
	
	got_iterator = SLLFind(got_from, got_to, IsMatchInt, &got_params);
	
	got_want = SLLBegin(got_list_1);
    for (i = 0; i < got_params - 5; i++)
    {
    	got_want = SLLNext(got_want); 
    }
    
    status = SLLIsEqual(got_want, got_iterator);
    TestInt(status, TRUE, __LINE__);
}

static void TestSetData(list_t *got_list_1)
{
	int data = 0;
	void *get_data = NULL;
	
	assert(NULL != got_list_1);
	
	SLLSetData(SLLBegin(got_list_1), &data);
	get_data = SLLGetData(SLLBegin(got_list_1));
	TestInt(SUCCESS, *(int *)get_data, __LINE__);
}

static void TestForEach(list_t *got_list_1)
{
	slist_iter_t got_from = NULL;
	slist_iter_t got_to = NULL;
	int got_params = 10;
	int status = 0;
	
	got_from = SLLBegin(got_list_1);
	got_to = SLLEnd(got_list_1);
	
	status = SLLForEach(got_from, got_to, ActFuncInt, &got_params);
	TestInt(SUCCESS, status, __LINE__);
}

static int IsMatchInt(void *want, void *got)
{
	if (*(int *)want == *(int *)got)
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

static void TestIsEmpty(int want, int got)
{
	if (want != got)
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
