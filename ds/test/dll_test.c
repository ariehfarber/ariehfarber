/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <string.h> /*strlen*/

#include "dll.h"

#define ERROR -1
#define SUCCESS 0
#define TRUE 1
#define FALSE 0

static void TestDLL();

int main()
{
	TestDLL();

	return (0);
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

static int ActFuncChar(void *node_data, void *parametrs)
{
	*(char *)node_data = *(char *)parametrs;
	
	if (*(char *)node_data != *(char *)parametrs)
	{
		return (ERROR);
	}
	
	return (SUCCESS);
}

static int IsMatchChar(void *node_data, void *parametrs)
{
	if (*(char *)node_data == *(char *)parametrs)
	{
		return (TRUE);
	}
	
	return (FALSE);
}

static void TestDLLInsert(dll_t *dll)
{
	dll_iter_t *insert_node = NULL;
	char data[] = "abcd";
	size_t size = 0;
	size_t i = 0;
	
	size = strlen(data);
	
	insert_node = DLLEnd(dll);
	
	for (i = 0; i < size; i++)
	{
		insert_node = DLLInsert(insert_node, &data[i]);
	}
		
	insert_node = DLLPushback(dll, &data[0]);
	DLLPopback(dll);
	insert_node = DLLPushfront(dll, &data[0]);
	DLLPopfront(dll);
}


static void TestForEach(dll_t *dll)
{
	dll_iter_t *test_from = NULL;
	dll_iter_t *test_to = NULL;
	char test_params = 'z';
	int status = 0;
	
	test_from = DLLBegin(dll);
	test_to = DLLNext(test_from);
	
	status = DLLForEach(test_from, test_to, ActFuncChar, &test_params);
	TestInt(SUCCESS, status, __LINE__);
}

static void TestFind(dll_t *dll)
{
	dll_iter_t *test_iterator = NULL;
	char params = 'z';
	int status = 0;
	
	test_iterator = DLLFind(DLLBegin(dll), DLLEnd(dll), IsMatchChar, &params);
   
    status = DLLIsEqual(DLLBegin(dll), test_iterator);
    TestInt(status, TRUE, __LINE__);
}

static void TestDLL()
{
	dll_t *dll = NULL;
	
	dll = DLLCreate();
	
	TestDLLInsert(dll);
	
	TestForEach(dll);
	
	TestFind(dll);
	
	DLLDestroy(dll);
}











