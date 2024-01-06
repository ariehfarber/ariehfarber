/*******************************************************************************
*Author: Arieh Farber
*Reviewer: Yarden Shai
*Date: 9/11/2023
*******************************************************************************/
#define _POSIX_C_SOURCE 200809L /*a macro for using strdup with c89 compiler*/

#include <stdio.h>   /*printf()										  */
#include <stddef.h>  /*size_t  										  */
#include <stdlib.h>  /*malloc  										  */
#include <assert.h>  /*assert										  */
#include <strings.h> /*strcasecmp								      */
#include <string.h>  /*strlen, strcmp, strncmp, , strcpy, strncpy...  */
	 
#include "String.h"

static void TestStrLen();
static void TestStrCmp();
static void TestStrNCmp();
static void TestStrCaseCmp();
static void TestStrCpy();
static void TestStrNCpy();
static void TestStrChr();
static void TestStrDup();
static void TestStrCat();
static void TestStrNCat();
static void TestStrStr();
static void TestStrSpn();

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

static void TestInt(int want, int got, int line);
static void TestChar(char *want, char *got, int line);

static void TestStrLen()
{
	const char str1[] = "Hello there";
	
	TestInt(strlen(str1), StrLen(str1), __LINE__);
}

static void TestStrCmp()
{
	const char *s1[] ={"check", "abc", "Ab"};
	const char *s2[] ={"check", "abc", "Ab"};
	int i = 0;
	int size = 3;
	
	for (i = 0; i < size; ++i)
	{
		TestInt(strcmp(s1[i], s2[i]), StrCmp(s1[i], s2[i]), __LINE__);
	}
}

static void TestStrNCmp()
{
	const char *s1[] ={"new check", "abcddefggrr", "AB"};
	const char *s2[] ={"new check", "abcc", "BC"};
	int i = 0;
	int size = 3;
	size_t n = 4; 

	for (i = 0; i < size; ++i)
	{
		TestInt(strncmp(s1[i], s2[i], n), StrNCmp(s1[i], s2[i], n), __LINE__);
	}
}

static void TestStrCaseCmp()
{
	const char *s1[] ={"NEW", "abc", "abcd"};
	const char *s2[] ={"nEw", "ABC", "AbCd"};
	int i = 0;
	int size = 3;

	for (i = 0; i < size; ++i)
	{
		TestInt(strcasecmp(s1[i], s2[i]), StrCaseCmp(s1[i], s2[i]), __LINE__);
	}
}

static void TestStrCpy()
{
	const char str1[] = "Here comes the sun";
	char *str2 = NULL; 
	
	str2 = (char *)malloc(StrLen(str1) + 1); 
	if (NULL == str2)
	{
        	printf("Memory allocation failed\n");
        	return; 
	}
	
	TestChar(strcpy(str2, str1), StrCpy(str2, str1), __LINE__);
	
	free(str2);
}

static void TestStrNCpy()
{
    const char str1[] = "Here comes the sun";
    char *str2 = NULL;
    char *str3 = NULL;
    size_t n = 4; 
    
    str2 = (char *)malloc(n + 1); 
    str3 = (char *)malloc(n + 1);
    if (NULL == str2 || NULL == str3)
    {
        printf("Memory allocation failed\n");
        free(str2); 
        free(str3);  
        return; 
    }

    memset(str2, 0, n + 1);
    memset(str3, 0, n + 1);

    strncpy(str2, str1, n); 
    StrNCpy(str3, str1, n); 

    TestChar(str2, str3, __LINE__); 

    free(str2); 
    free(str3); 
}

static void TestStrChr()
{
	const char str1[] = "Here we go again";
	int symbol = 'g';

	TestChar(strchr(str1, symbol), StrChr(str1, symbol), __LINE__);
}

static void TestStrDup()
{
    const char str1[] = "Wait, am I the clone?";
    char *duplicated_str1 = NULL;
    char *duplicated_str2 = NULL;
    
    duplicated_str1 = strdup(str1); 
    duplicated_str2 = StrDup(str1); 

    TestChar(duplicated_str1, duplicated_str2, __LINE__); 

    free(duplicated_str1); 
    free(duplicated_str2);
}

static void TestStrCat()
{
	char str1[30] = "Every beginning, ";
	const char str2[] = "Has an end";
	
	TestChar(strcat(str1, str2), StrCat(str1, str2), __LINE__);
}

static void TestStrNCat()
{
	char str1[30] = "Every beginning, ";
	const char str2[] = "Has an end";
	size_t n = 4;
	
	TestChar(strncat(str1, str2, n), StrNCat(str1, str2, n), __LINE__);
}

static void TestStrStr()
{
	const char str1[] = "Like looking for a needle in a haystack";
	const char str2[] = "needle";

	TestChar(strstr(str1, str2), StrStr(str1, str2), __LINE__);
}

static void TestStrSpn()
{
	const char str1[] = "ababbcd123456abc";
	const char str2[] = "abcd";
	
	TestInt(strspn(str1, str2), StrSpn(str1, str2), __LINE__);
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

static void TestChar(char *want, char *got, int line)
{
	if (0 != strcmp(want, got))
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
