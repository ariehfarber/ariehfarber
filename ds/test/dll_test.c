/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <string.h> /*strlen*/

#include "dll.h"

static void TestDLL();

int main()
{
	TestDLL();

	return (0);
}

static void TestDLLInsert(dll_t *dll)
{
	dll_iter_t *insert_node = NULL;
	char *data = "abcd";
	size_t size = 0;
	size_t i = 0;
	
	size = strlen(data);
	
	insert_node = DLLPushback(dll, &data[0]);
	insert_node = DLLPushfront(dll, &data[0]);
	
	insert_node = DLLEnd(dll);
	
	for (i = 0; i < size; i++)
	{
		insert_node = DLLInsert(insert_node, &data[i]);
	}
}


static void TestDLL()
{
	dll_t *dll = NULL;
	
	dll = DLLCreate();
	
	TestDLLInsert(dll);
	
	DLLDestroy(dll);
}
