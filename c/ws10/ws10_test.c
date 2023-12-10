/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Ben Cohen
*Date: 27/11/2023
*******************************************************************************/
#include <stdio.h>  /*printf								 */
#include <stddef.h> /*size_t								 */
#include <string.h> /*strcmp, strcpy, memset, memcpy, memmove*/

#include "ws10.h"

static void TestMemSet();
static void TestMemCpy();
static void TestMemMove();

int main()
{
	TestMemSet();
	TestMemCpy();
	TestMemMove();
	
	return (0);
}

static void TestNChar(char *control, char *test, size_t n, int line)
{
	while (0 < n)
	{
		if(control[n - 1] != test[n - 1])
		{
			printf("\033[0;31m");
			printf("Error. failed at line %d\n", line);
			printf("\033[0m"); 
			break;
		}
		n--;	
	}
	if (0 == n)
	{
		printf("\033[1;32m");
		printf("Success!\n");
		printf("\033[0m"); 
	}
}

static void TestMemSet()
{
	char original_string[] = "12345678_12345678";
	char test_string[20];
	char control_string[20];
	int character = 300;
	size_t number_of_bytes = 10;
	
	memset(test_string, 0, sizeof(test_string));  
    memset(control_string, 0, sizeof(control_string));  
    
    strcpy(test_string, original_string);
	MemSet(test_string, character, number_of_bytes);
	
	strcpy(control_string, original_string);
	memset(control_string, character, number_of_bytes);
	
	TestNChar(control_string, test_string, number_of_bytes, __LINE__);
	
	memset(test_string, 0, sizeof(test_string));  
    memset(control_string, 0, sizeof(control_string));  
    
    strcpy(test_string, original_string);
	MemSet(test_string + 1, character, number_of_bytes);
	
	strcpy(control_string, original_string);
	memset(control_string + 1, character, number_of_bytes);
	
	TestNChar(control_string, test_string, number_of_bytes, __LINE__);
}

static void TestMemCpy()
{
	char original_string[] = "12345678_12345678";
	char test_string[30];
	char control_string[30];
	size_t number_of_bytes = 10;
	
	memset(test_string, 0, sizeof(test_string));  
    memset(control_string, 0, sizeof(control_string));  

	MemCpy(test_string, original_string, number_of_bytes);
	
	memcpy(control_string, original_string, number_of_bytes);
		
	TestNChar(control_string, test_string, number_of_bytes, __LINE__);
	
	memset(test_string, 0, sizeof(test_string));  
    memset(control_string, 0, sizeof(control_string));  

	MemCpy(test_string + 1, original_string, number_of_bytes);
	
	memcpy(control_string + 1, original_string, number_of_bytes);
		
	TestNChar(control_string, test_string, number_of_bytes, __LINE__);
}

static void TestMemMove()
{
	char test_string[10] = "123456789";
	char control_string[10] = "123456789";
	size_t number_of_bytes = 4;

	MemMove(test_string + 2, test_string, number_of_bytes);
	
	memmove(control_string + 2, control_string, number_of_bytes);
		
	TestNChar(control_string, test_string, number_of_bytes, __LINE__);
}
