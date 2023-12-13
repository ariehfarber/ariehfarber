/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Omer Bruker
*Date: 12/12/2023
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

/*static void PrintDLL(dll_t *dll)*/
/*{*/
/*	dll_iter_t runner = NULL;*/
/*	void *data = NULL;*/
/*	size_t i = 0;*/
/*	size_t size = 0;*/
/*	*/
/*	size = DLLSize(dll);*/
/*	*/
/*	runner = DLLBegin(dll);*/
/*	*/
/*	for (i = 0; i < size; i++)*/
/*	{*/
/*		data = DLLGet(runner);*/
/*		printf("%c\n", *(char *)data);*/
/*		runner = DLLNext(runner);	*/
/*	}*/
/*	printf("\n");*/
/*}*/

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
	dll_iter_t insert_node = NULL;
	static char data[] = "mbcd";
	static char letter = 'a';
	size_t str_size = 0;
	size_t i = 0;
	
	str_size = strlen(data);
	
	insert_node = DLLEnd(dll);
	
	for (i = 0; i < str_size; i++)
	{
		insert_node = DLLInsert(dll, insert_node, &data[i]);
		insert_node = DLLNext(insert_node);
	}
	DLLSet(DLLBegin(dll), &letter);
		
	insert_node = DLLPushback(dll, &data[0]);
	DLLPopback(dll);
	insert_node = DLLPushfront(dll, &data[0]);
	DLLPopfront(dll);
}

static void TestForEach(dll_t *dll)
{
	dll_iter_t test_from = NULL;
	dll_iter_t test_to = NULL;
	char test_params = 'z';
	int status = 0;
	
	test_from = DLLBegin(dll);
	test_to = DLLNext(test_from);
	
	status = DLLForEach(test_from, test_to, ActFuncChar, &test_params);
	TestInt(SUCCESS, status, __LINE__);
}

static void TestFind(dll_t *dll)
{
	dll_iter_t test_iterator = NULL;
	dll_iter_t test_from = NULL;
	dll_iter_t test_to = NULL;
	char params = 'z';
	int status = 0;
	
	test_from = DLLBegin(dll);
	test_to = DLLEnd(dll);
	
	test_iterator = DLLFind(test_from, test_to, IsMatchChar, &params);
   
    status = DLLIsEqual(DLLBegin(dll), test_iterator);
    TestInt(status, TRUE, __LINE__);
}

static void TestDLLMultiFind(dll_t *dll)
{
	int status = 0;
	dll_t *dll_output = NULL;
	dll_iter_t test_from = NULL;
	dll_iter_t test_to = NULL;
	char params = 'm';
	
	dll_output = DLLCreate();
	
	test_from = DLLBegin(dll);
	test_to = DLLEnd(dll);

	status = DLLMultiFind(test_from, test_to, IsMatchChar, &params, dll_output);
    TestInt(status, SUCCESS, __LINE__);
    					  
	DLLDestroy(dll_output);
}

static void TestDLLSplice(dll_t *dll)
{
	dll_t *dll_splice = NULL;
	dll_iter_t test_from = NULL;
	dll_iter_t test_to = NULL;
	dll_iter_t test_where = NULL;
	dll_iter_t insert_node = NULL;
	static char data[] = "abcd";
	size_t size = 0;
	size_t i = 0;
	
	dll_splice = DLLCreate();
	size = strlen(data);
	insert_node = DLLEnd(dll_splice);
	for (i = 0; i < size; i++)
	{
		insert_node = DLLInsert(dll_splice, insert_node, &data[i]);
		insert_node = DLLNext(insert_node);
	}
	
	test_from = DLLBegin(dll_splice);
	test_to = DLLEnd(dll_splice);
	test_where = DLLBegin(dll);

	DLLSplice(test_from, test_to, test_where);
	
	DLLDestroy(dll_splice);
}

static void TestState(dll_t *dll, size_t control_size, int control_state)
{
	TestInt(control_size, DLLSize(dll), __LINE__);
	TestInt(control_state, DLLIsEmpty(dll), __LINE__);
}

static void TestDLL()
{
	dll_t *dll = NULL;
	
	dll = DLLCreate();
	TestState(dll, 0, TRUE);

	TestDLLInsert(dll);
	TestState(dll, 4, FALSE);
	
	TestForEach(dll);
	
	TestFind(dll);
	
	TestDLLSplice(dll);
			
	TestDLLMultiFind(dll);
	
	DLLDestroy(dll);
}
