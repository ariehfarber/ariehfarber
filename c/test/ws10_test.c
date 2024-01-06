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

static void TestNChar(char *want, char *got, size_t n, int line);

static void TestMemSet()
{
	char original_string[] = "12345678_12345678";
	char got_string[20];
	char want_string[20];
	int character = 300;
	size_t number_of_bytes = 10;
	
	memset(got_string, 0, sizeof(got_string));  
    memset(want_string, 0, sizeof(want_string));  
    
    strcpy(got_string, original_string);
	MemSet(got_string, character, number_of_bytes);
	
	strcpy(want_string, original_string);
	memset(want_string, character, number_of_bytes);
	
	TestNChar(want_string, got_string, number_of_bytes, __LINE__);
	
	memset(got_string, 0, sizeof(got_string));  
    memset(want_string, 0, sizeof(want_string));  
    
    strcpy(got_string, original_string);
	MemSet(got_string + 1, character, number_of_bytes);
	
	strcpy(want_string, original_string);
	memset(want_string + 1, character, number_of_bytes);
	
	TestNChar(want_string, got_string, number_of_bytes, __LINE__);
}

static void TestMemCpy()
{
	char original_string[] = "12345678_12345678";
	char got_string[30];
	char want_string[30];
	size_t number_of_bytes = 10;
	
	memset(got_string, 0, sizeof(got_string));  
    memset(want_string, 0, sizeof(want_string));  

	MemCpy(got_string, original_string, number_of_bytes);
	
	memcpy(want_string, original_string, number_of_bytes);
		
	TestNChar(want_string, got_string, number_of_bytes, __LINE__);
	
	memset(got_string, 0, sizeof(got_string));  
    memset(want_string, 0, sizeof(want_string));  

	MemCpy(got_string + 1, original_string, number_of_bytes);
	
	memcpy(want_string + 1, original_string, number_of_bytes);
		
	TestNChar(want_string, got_string, number_of_bytes, __LINE__);
}

static void TestMemMove()
{
	char got_string[10] = "123456789";
	char want_string[10] = "123456789";
	size_t number_of_bytes = 4;

	MemMove(got_string + 2, got_string, number_of_bytes);
	
	memmove(want_string + 2, want_string, number_of_bytes);
		
	TestNChar(want_string, got_string, number_of_bytes, __LINE__);
}

static void TestNChar(char *want, char *got, size_t n, int line)
{
	while (0 < n)
	{
		if(want[n - 1] != got[n - 1])
		{
			printf("\033[0;31m");
			printf("Error. failed at line %d\n", line);
			printf("\033[0m"); 
			break;
		}
		--n;	
	}
	if (0 == n)
	{
		printf("\033[1;32m");
		printf("Success!\n");
		printf("\033[0m"); 
	}
}
