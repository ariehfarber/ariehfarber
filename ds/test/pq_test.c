/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Omer Bruker 
*Date: 21/12/2023
*******************************************************************************/
#include <stdio.h> /*printf*/

#include "pq.h"

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define ERROR -1


static void TestPQ();

int main()
{
	TestPQ();
	
	return (0);
}

/*static void PrintPQ(pq_t *pq)*/
/*{*/
/*	size_t size = 0;*/
/*	size_t i = 0;*/
/*	void *data = NULL;*/
/*	*/
/*	size = PQSize(pq);*/
/*		*/
/*	for (i = 0; i < size; i++)*/
/*	{		*/
/*		data = PQDequeue(pq);*/
/*		printf("%d\n", *(int *)data);*/
/*	}*/
/*}*/

static int IsMatchInt(void *node_data, void *parametrs)
{
	if (*(int *)node_data == *(int *)parametrs)
	{
		return (TRUE);
	}
	
	return (FALSE);
}

static void TestInt(int control, int test, int line)
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

static void TestData(void *control, void *test, int line)
{
	if (*(int *)control != *(int *)test)
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

static void TestState(pq_t *pq, size_t control_size, int control_state)
{
	TestInt(control_size, PQSize(pq), __LINE__);
	TestInt(control_state, PQIsEmpty(pq), __LINE__);
}

static int CompFuncInt(void *node_data, void *parametr)
{
	return (*(int *)node_data - *(int *)parametr);
}

static size_t TestEnqueue(pq_t *pq)
{
	static int data_array[] = {1, 3, 5, 7, 89, -55, -100, 0};
	size_t array_size = 0;
	size_t i = 0;
	int state = SUCCESS;

	array_size = sizeof(data_array) / sizeof(data_array[0]);
	
	for (i = 0; i < array_size; i++)
	{
		state = PQEnqueue(pq, &data_array[i]);
		TestInt(SUCCESS, state, __LINE__);	
	}
	
	return (array_size);
}

static void TestDequeue(pq_t *pq)
{
	void *data_test_1 = NULL;
	void *data_test_2 = NULL;
	
	data_test_1 = PQPeek(pq);
	data_test_2 = PQDequeue(pq);
	TestData(data_test_1, data_test_2, __LINE__);
}

static void TestErase(pq_t* pq)
{
	void *data = NULL;
	int params = 5;
	size_t size = 0;
	
	size = PQSize(pq);
	
	data = PQErase(pq, IsMatchInt, &params);
	TestInt(params, *(int *)data, __LINE__);
	TestState(pq, size, FALSE);
}

static void TestPQ()
{
	pq_t *pq = NULL;
	size_t size = 0;
	
	pq = PQCreate(CompFuncInt);
	TestState(pq, size, TRUE);
	
	TestEnqueue(pq);
	TestState(pq, size, FALSE);
	
	TestErase(pq);
	
	TestDequeue(pq);
	TestState(pq, size, FALSE);
	
	TestEnqueue(pq);
	TestState(pq, size, FALSE);
	
	PQClear(pq);
	TestState(pq, 0, TRUE);
	
	PQDestroy(pq);
}
