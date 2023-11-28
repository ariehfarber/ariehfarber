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

static void TestResultNChar(char *control, char *result, size_t n, int line)
{
	while (n > 0)
	{
		if(control[n - 1] != result[n - 1])
		{
			printf("\033[0;31m");
			printf("Error. failed at line %d\n", line);
			printf("\033[0m"); 
		}
		n--;	
	}
}

static void TestMemSet()
{
	char original_string[] = "12345678_12345678";
	char test_string[20];
	char control_string[20];
	int character = 300;
	size_t number_of_bytes = 10;
	
	/*Initialize the buffers*/
	memset(test_string, 0, sizeof(test_string));  
    memset(control_string, 0, sizeof(control_string));  
    
	/*test for aligned string*/
    strcpy(test_string, original_string);
	MemSet(test_string, character, number_of_bytes);
	
	strcpy(control_string, original_string);
	memset(control_string, character, number_of_bytes);
	
	TestResultNChar(control_string, test_string, number_of_bytes, __LINE__);
	
	/*Reinitialize the buffers*/
	memset(test_string, 0, sizeof(test_string));  
    memset(control_string, 0, sizeof(control_string));  
    
	/*test for unaligned string*/
    strcpy(test_string, original_string);
	MemSet(test_string + 1, character, number_of_bytes);
	
	strcpy(control_string, original_string);
	memset(control_string + 1, character, number_of_bytes);
	
	TestResultNChar(control_string, test_string, number_of_bytes, __LINE__);
}

static void TestMemCpy()
{
	char original_string[] = "12345678_12345678";
	char test_string[30];
	char control_string[30];
	size_t number_of_bytes = 10;
	
	/*Initialize the buffers*/
	memset(test_string, 0, sizeof(test_string));  
    memset(control_string, 0, sizeof(control_string));  

	/*test for aligned string*/
	MemCpy(test_string, original_string, number_of_bytes);
	
	memcpy(control_string, original_string, number_of_bytes);
		
	TestResultNChar(control_string, test_string, number_of_bytes, __LINE__);
	
	/*Reinitialize the buffers*/
	memset(test_string, 0, sizeof(test_string));  
    memset(control_string, 0, sizeof(control_string));  

	/*test for unaligned string*/
	MemCpy(test_string + 1, original_string, number_of_bytes);
	
	memcpy(control_string + 1, original_string, number_of_bytes);
		
	TestResultNChar(control_string, test_string, number_of_bytes, __LINE__);
}

static void TestMemMove()
{
	char test_string[10] = "123456789";
	char control_string[10] = "123456789";
	size_t number_of_bytes = 4;

	/*test for unaligned string*/
	MemMove(test_string + 2, test_string, number_of_bytes);
	
	memmove(control_string + 2, control_string, number_of_bytes);
		
	TestResultNChar(control_string, test_string, number_of_bytes, __LINE__);
}
