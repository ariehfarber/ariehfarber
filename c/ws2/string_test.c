/***********************************************************************************
*Auther: Arieh Farber
*Reviewr: Omer Bruker
*Date: 7/11/2023
***********************************************************************************/

#include <stddef.h> /*size_t  */
#include <stdio.h>  /*printf()*/
#include <stdlib.h> /*malloc  */
#include "string.h"

void TestStrLen();
void TestStrCmp();
void TestStrCpy();
void TestStrNCpy();
void TestStrNCmp();
void TestStrCaseCmp();

int main()
{
	TestStrLen();
	TestStrCmp();
	TestStrCpy();
	TestStrNCpy();
	TestStrNCmp();
	TestStrCaseCmp();
	
	return (0);
}

void TestStrLen()
{
	char string[] = "Hello there";
	size_t length = StrLen(string);
	
	printf("The length of \"%s\" is: %lu\n\n", string, length);
}

void TestStrCmp()
{
	char *string1[] ={"check", "abc", "ab"};
	char *string2[] ={"check", "abcc", "Ab"};
	int i = 0, size = 3;
	
	for(i = 0; i < size; i++)
	{
	int value = StrCmp(string1[i], string2[i]);
		if(value > 0)
		{
			printf("string1: \"%s\" ,string2: \"%s\"\n", 
			string1[i], string2[i]);
			printf("string1 \"%s\"  is longer\n\n", string1[i]);
		}
		else if(value < 0)
		{
			printf("string1: \"%s\" ,string2: \"%s\"\n", 
			string1[i], string2[i]);
			printf("string2 \"%s\" is longer\n\n", string2[i]);
		}
		else if(value == 0)
		{
			printf("string1: \"%s\" ,string2: \"%s\"\n", 
			string1[i], string2[i]);
			printf("strings are equal\n\n");
		}
	}
}

void TestStrNCmp()
{
	char *string1[] ={"new check", "abcddefggrr", "abcdefghijklmnop"};
	char *string2[] ={"new check", "abcc", "abcdeFGhijklmnop"};
	int i = 0, size = 3;
	size_t limit = 3; 
	
	for(i = 0; i < size; i++)
	{
	int value = StrNCmp(string1[i], string2[i], limit);
		if(value > 0)
		{
			printf("string1: \"%s\" ,string2: \"%s\"\n", 
			string1[i], string2[i]);
			printf("up to %lu charecters, string1 is longer\n\n", 
			limit);		
		}
		else if(value < 0)
		{
			printf("string1: \"%s\" ,string2: \"%s\"\n", 
			string1[i], string2[i]);
			printf("up to %lu charecters, string2 is longer\n\n", 
			limit);
		}
		else if(value == 0)
		{
			printf("string1: \"%s\" ,string2: \"%s\"\n", 
			string1[i], string2[i]);
			printf("up to %lu charecters, Strings are equal\n\n", limit);
		}
	}
}

void TestStrCpy()
{
	char string[] = "Here comes the sun";
	char *copied_string = NULL; 
	
	copied_string = (char *)malloc(StrLen(string) + 1); 

	StrCpy(copied_string, string);
	
	printf("Original string: \"%s\", ", string);
	printf("Copied string: \"%s\"\n\n", copied_string);
}

void TestStrNCpy()
{
	char string[] = "Here comes the sun";
	char *copied_string = NULL;
	size_t limit = 4; 
	
	copied_string = (char *)malloc(limit + 1); 

	StrNCpy(copied_string, string, limit);
	
	printf("Original string: \"%s\", ", string);
	printf("Copied %lu charecters of the string: \"%s\"\n\n", limit, 	
	copied_string);
}

TestStrCaseCmp()
{

}




















