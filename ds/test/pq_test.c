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

static void TestState(pq_t *pq, size_t want_size, int want_state);
static int CompFuncInt(void *node_data, void *parametr);
static size_t TestEnqueue(pq_t *pq);
static size_t TestDequeue(pq_t *pq);
static void TestErase(pq_t* pq);
static int IsMatchInt(void *node_data, void *parametrs);
static void TestInt(int want, int got, int line);
static void TestData(void *want, void *got, int line);

static void TestPQ()
{
	pq_t *pq = NULL;
	size_t size = 0;
	
	pq = PQCreate(CompFuncInt);
	TestState(pq, size, TRUE);
	
	size = TestEnqueue(pq);
	TestState(pq, size, FALSE);
	
	TestErase(pq);
	
	size = TestDequeue(pq);
	TestState(pq, size, FALSE);
	
	PQClear(pq);
	TestState(pq, 0, TRUE);
	
	PQDestroy(pq);
}

static void TestState(pq_t *pq, size_t want_size, int want_state)
{
	TestInt(want_size, PQSize(pq), __LINE__);
	TestInt(want_state, PQIsEmpty(pq), __LINE__);
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

static size_t TestDequeue(pq_t *pq)
{
	void *data_got_1 = NULL;
	void *data_got_2 = NULL;
	
	data_got_1 = PQPeek(pq);
	data_got_2 = PQDequeue(pq);
	TestData(data_got_1, data_got_2, __LINE__);
	
	return (PQSize(pq));
}

static void TestErase(pq_t* pq)
{
	void *data = NULL;
	int params = 5;
	size_t size = 0;
	
	data = PQErase(pq, IsMatchInt, &params);
	TestInt(params, *(int *)data, __LINE__);
	size = PQSize(pq);
	TestState(pq, size, FALSE);
}

static int IsMatchInt(void *node_data, void *parametrs)
{
	if (*(int *)node_data == *(int *)parametrs)
	{
		return (TRUE);
	}
	
	return (FALSE);
}

static void TestInt(int want, int got, int line)
{
	if (want != got)
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

static void TestData(void *want, void *got, int line)
{
	if (*(int *)want != *(int *)got)
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
