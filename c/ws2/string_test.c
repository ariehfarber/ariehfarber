/***********************************************************************************
*Author: Arieh Farber
*Reviewer: Yarden Shai
*Date: 9/11/2023
***********************************************************************************/

#include <stdio.h>  /*printf()*/
#include <stddef.h> /*size_t  */
#include <stdlib.h> /*malloc  */
#include <assert.h> /*assert */
#include "string.h"

void TestStrLen();
void TestStrCmp();
void TestStrNCmp();
void TestStrCaseCmp();
void TestStrCpy();
void TestStrNCpy();
void TestStrChr();
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
	TestStrChr();
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
			printf("str1 is lexicographicaly greater\n\n");
		}
		else if(value < 0)
		{
			printf("str1: \"%s\" ,str2: \"%s\"\n", 
			str1[i], str2[i]);
			printf("str2 is lexicographicaly greater\n\n");
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
	char *str1[] ={"new check", "abcddefggrr", "AB"};
	char *str2[] ={"new check", "abcc", "BC"};
	int i = 0, size = 3;
	size_t n = 4; 
	int value = 0;
	
	printf("TestStrNCmp-\n");
	for(i = 0; i < size; i++)
	{
		value = StrNCmp(str1[i], str2[i], n);
		if(value > 0)
		{
			printf("str1: \"%s\" ,str2: \"%s\"\n", 
			str1[i], str2[i]);
			printf("str1 > (lexico) for %lu characters\n\n", n);		
		}
		else if(value < 0)
		{
			printf("str1: \"%s\" ,str2: \"%s\"\n", 
			str1[i], str2[i]);
			printf("str2 > (lexico) for %lu characters\n\n", n);
		}
		else if(value == 0)
		{
			printf("str1: \"%s\" ,str2: \"%s\"\n", 
			str1[i], str2[i]);
			printf("up to %lu charecters at least, they are equal\n\n", 			
			n);
		}
	}
}

void TestStrCaseCmp()
{
	char *str1[] ={"NEW", "abc", "abcd"};
	char *str2[] ={"check", "ABC", "AbCd"};
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
			printf("str1 is lexicographicaly greater\n\n");
		}
		else if(value < 0)
		{
			printf("str1: \"%s\" ,str2: \"%s\"\n", 
			str1[i], str2[i]);
			printf("str2 is lexicographicaly greater\n\n");
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
	assert(NULL != copied_str1);

	StrCpy(copied_str1, str1);
	
	printf("TestStrCpy-\n");
	printf("Original string: \"%s\", ", str1);
	printf("Copied string: \"%s\"\n\n", copied_str1);
	
	free(copied_str1);
	copied_str1 = NULL;
}

void TestStrNCpy()
{
	char str1[] = "Here comes the sun";
	char *copied_str1 = NULL;
	size_t n = 4; 
	
	copied_str1 = (char *)malloc(n + 1); 
	assert(NULL != copied_str1);
	
	StrNCpy(copied_str1, str1, n);
	
	printf("TestStrNCpy-\n");
	printf("Original string: \"%s\", ", str1);
	printf("Copied %lu charecters of the string: \"%s\"\n\n", n, 	
	copied_str1);
	
	free(copied_str1);
	copied_str1 = NULL;
}

void TestStrChr()
{
	char str1[] = "Here we go again";
	int symbol = 'g';
	char *check = NULL;
	
	check = StrChr(str1, symbol);
	
	printf("TestStrChr-\n");
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
	
	free(duplicated_str1);
	duplicated_str1 = NULL;
}

void TestStrCat()
{
	char str1[30] = "Every beginning, ";
	char str1_copy[30] = "Every beginning, ";
	char str2[] = "Has an end";
	char *str3 = NULL;
	
	str3 = StrCat(str1, str2);
	
	printf("TestStrCat-\n");
	printf("String 1: \"%s\", String 2: \"%s\"\n", str1_copy, str2);
	printf("concatenated string: \"%s\"\n\n", str3);
}

void TestStrNCat()
{
	char str1[30] = "Every beginning, ";
	char str1_copy[30] = "Every beginning, ";
	char str2[] = "Has an end";
	size_t n = 4;
	
	StrNCat(str1, str2, n);
	
	printf("TestStrNCat-\n");
	printf("string1: \"%s\", string2: \"%s\"\n", str1_copy, str2);
	printf("concatenated string up to n = %lu: \"%s\"\n\n", n, str1);
}

void TestStrStr()
{
	char str1[] = "Like looking for a needle in a haystack";
	char str2[] = "needle";
	char *ptr = NULL;
	
	ptr = StrStr(str1, str2);
	
	printf("TestStrStr-\n");
	if(NULL != ptr)
	{
	printf("returned string from the function: \"%s\".\n", ptr);
	printf("\"%s\" exists in the string \"%s\"\n\n", str2, str1);
	}
	else
	{
	printf("function not working\n\n");
	}
}

void TestStrSpn()
{
	char str1[] = "ababbcd123456abc";
	char str2[] = "abcd";
	size_t n = 0;
	
	n = StrSpn(str1, str2);
	
	printf("TestStrSpn-\n");
	printf("string1: \"%s\", string2: \"%s\"\n", str1, str2);
	printf("After %lu charecters, we reach a non string2 charecter\n\n", n);
}

















