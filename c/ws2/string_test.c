/***********************************************************************************
*Auther: Arieh Farber
*Reviewr: Omer Bruker
*Date: 7/11/2023
***********************************************************************************/

#include <stdio.h>  /*printf()*/
#include <stddef.h> /*size_t  */
#include <stdlib.h> /*malloc  */
#include "string.h"

void TestStrLen();
void TestStrCmp();
void TestStrNCmp();
void TestStrCaseCmp();
void TestStrCpy();
void TestStrNCpy();
void TestStrChar();
void TestStrDup();
void TestStrCat();
void TestStrNCat();
void TestStrStr();
void TestStrSpn();

int main()
{
	TestStrLen();
	TestStrCmp();
	TestStrNCmp();
	TestStrCaseCmp();
	TestStrCpy();
	TestStrNCpy();
	TestStrChar();
	TestStrDup();
	TestStrCat();
	TestStrNCat();
	TestStrStr();
	TestStrSpn();
	
	return (0);
}

void TestStrLen()
{
	char str1[] = "Hello there";
	size_t length = StrLen(str1);
	
	printf("TestStrLen-\n");
	printf("The length of \"%s\" is: %lu charecters\n\n", str1, length);
}

void TestStrCmp()
{
	char *str1[] ={"check", "abc", "ab"};
	char *str2[] ={"check", "abcc", "Ab"};
	int i = 0, size = 3;
	int value = 0;
	
	printf("TestStrCmp-\n");
	for(i = 0; i < size; i++)
	{
		value = StrCmp(str1[i], str2[i]);
		if(value > 0)
		{
			printf("str1: \"%s\" ,str2: \"%s\"\n", 
			str1[i], str2[i]);
			printf("str1 \"%s\"  is longer\n\n", str1[i]);
		}
		else if(value < 0)
		{
			printf("str1: \"%s\" ,str2: \"%s\"\n", 
			str1[i], str2[i]);
			printf("str2 \"%s\" is longer\n\n", str2[i]);
		}
		else if(value == 0)
		{
			printf("str1: \"%s\" ,str2: \"%s\"\n", 
			str1[i], str2[i]);
			printf("strings are equal\n\n");
		}
	}
}

void TestStrNCmp()
{
	char *str1[] ={"new check", "abcddefggrr", "abcdefghijklmnop"};
	char *str2[] ={"new check", "abcc", "abcdeFGhijklmnop"};
	int i = 0, size = 3;
	size_t limit = 3; 
	int value = 0;
	
	printf("TestStrNCmp-\n");
	for(i = 0; i < size; i++)
	{
		value = StrNCmp(str1[i], str2[i], limit);
		if(value > 0)
		{
			printf("str1: \"%s\" ,str2: \"%s\"\n", 
			str1[i], str2[i]);
			printf("up to %lu charecters at least, str1 is longer\n\n", 
			limit);		
		}
		else if(value < 0)
		{
			printf("str1: \"%s\" ,str2: \"%s\"\n", 
			str1[i], str2[i]);
			printf("up to %lu charecters at least, str2 is longer\n\n", 
			limit);
		}
		else if(value == 0)
		{
			printf("str1: \"%s\" ,str2: \"%s\"\n", 
			str1[i], str2[i]);
			printf("up to %lu charecters at least, they are equal\n\n", 			
			limit);
		}
	}
}

void TestStrCaseCmp()
{
	char *str1[] ={"NEW check", "abc", "ab"};
	char *str2[] ={"check", "ABC", "Ab"};
	int i = 0, size = 3;
	int value = 0;
	
	printf("TestStrCaseCmp-\n");
	for(i = 0; i < size; i++)
	{
		value = StrCaseCmp(str1[i], str2[i]);
		if(value > 0)
		{
			printf("str1: \"%s\" ,str2: \"%s\"\n", 
			str1[i], str2[i]);
			printf("str1 \"%s\"  is longer\n\n", str1[i]);
		}
		else if(value < 0)
		{
			printf("str1: \"%s\" ,str2: \"%s\"\n", 
			str1[i], str2[i]);
			printf("str2 \"%s\" is longer\n\n", str2[i]);
		}
		else if(value == 0)
		{
			printf("str1: \"%s\" ,str2: \"%s\"\n", 
			str1[i], str2[i]);
			printf("strings are equal\n\n");
		}
	}
}

void TestStrCpy()
{
	char str1[] = "Here comes the sun";
	char *copied_str1 = NULL; 
	
	copied_str1 = (char *)malloc(StrLen(str1) + 1); 

	StrCpy(copied_str1, str1);
	
	printf("TestStrCpy-\n");
	printf("Original string: \"%s\", ", str1);
	printf("Copied string: \"%s\"\n\n", copied_str1);
	
	free(copied_str1);
}

void TestStrNCpy()
{
	char str1[] = "Here comes the sun";
	char *copied_str1 = NULL;
	size_t limit = 4; 
	
	copied_str1 = (char *)malloc(limit + 1); 

	StrNCpy(copied_str1, str1, limit);
	
	printf("TestStrNCpy-\n");
	printf("Original string: \"%s\", ", str1);
	printf("Copied %lu charecters of the string: \"%s\"\n\n", limit, 	
	copied_str1);
	
	free(copied_str1);
}

void TestStrChar()
{
	char str1[] = "Here we go again";
	int symbol = 'g';
	char *check = NULL;
	
	check = StrChar(str1, symbol);
	
	printf("TestStrChar-\n");
	if (check != NULL)
	{
		printf("String: \"%s\"\n", str1);
		printf("string after %c is \"%s\"\n\n", symbol, check);
	}
	else
	{
		printf("Character %c not found in the string.\n\n", symbol);
	}
}

void TestStrDup()
{
	char str1[] = "Wait, am I the clone?";
	char *duplicated_str1 = NULL;
	
	duplicated_str1 = StrDup(str1);
	
	printf("TestStrDup-\n");
	printf("Original string: \"%s\", ", str1);
	printf("Duplicated string: \"%s\"\n\n", duplicated_str1);
	
	/*when using StrDup the user is responsible for freeing the memory*/
	free(duplicated_str1);
}

void TestStrCat()
{
	char str1[] = "Every beginning, ";
	char str1_copy[] = "Every beginning, ";
	char str2[] = "Has an end";
	char *str3 = NULL;
	size_t total_length = StrLen(str1) + StrLen(str2) + 1;
	
	str3 = (char *)malloc(total_length);
	
	str3 = StrCat(str1, str2);
	
	printf("TestStrCat-\n");
	printf("string1: \"%s\", string2: \"%s\"\n", str1_copy, str2);
	printf("concatenated string: \"%s\"\n\n", str3);
}

void TestStrNCat()
{
	char str1[] = "Every beginning, ";
	char str1_copy[] = "Every beginning, ";
	char str2[] = "Has an end";
	char *str3 = NULL;
	size_t limit = 4;
	size_t total_length = StrLen(str1) + limit + 1;
	
	str3 = (char *)malloc(total_length);
	
	str3 = StrNCat(str1, str2, limit);
	
	printf("TestStrNCat-\n");
	printf("string1: \"%s\", string2: \"%s\"\n", str1_copy, str2);
	printf("concatenated string up to limit %lu: \"%s\"\n\n", limit, str3);
}

void TestStrStr()
{
	char str1[] = "Like looking for a needle in a haystack";
	char str2[] = "needle";
	char *ptr = NULL;
	
	ptr = StrStr(str1, str2);
	
	printf("TestStrStr-\n");
	printf("returned string from the function: \"%s\".\n", ptr);
	printf("\"%s\" exists in the string \"%s\"\n\n", str2, str1);	
}

void TestStrSpn()
{
	char str1[] = "Like looking needle for a needle in a needle haystack";
	char str2[] = "needle";
	size_t appears = 0;
	
	appears = StrSpn(str1, str2);
	
	printf("TestStrSpn-\n");
	printf("\"%s\" is in the string \"%s\" %lu times\n\n", str2, str1, appears);	
}

















