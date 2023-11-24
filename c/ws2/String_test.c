/*******************************************************************************
*Author: Arieh Farber
*Reviewer: Yarden Shai
*Date: 9/11/2023
*******************************************************************************/
#define _POSIX_C_SOURCE 200809L /*a macro for using strdup with c89 compiler*/

#include <stdio.h>   /*printf()											 */
#include <stddef.h>  /*size_t  											 */
#include <stdlib.h>  /*malloc  											 */
#include <assert.h>  /*assert											 */
#include <strings.h> /*strcasecmp										 */
#include <string.h>  /*strlen, strcmp, strncmp, , strcpy, strncpy  	     */
					 /*strchr, strdup, strcat, strncat, strstr, strspn   */
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

static void TstResInt(int control, int func_res, int line)
{
	if (control != func_res)
	{
		printf("\033[0;31m");
		printf("Error. failed at line %d\n", line);
		printf("\033[0m"); 
	}
}

static void TstResChar(char *control, char *func_res, int line)
{
	if (strcmp(control, func_res))
	{
		printf("\033[0;31m");
		printf("Error. failed at line %d\n", line);
		printf("\033[0m"); 
	}
}

static void TestStrLen()
{
	const char str1[] = "Hello there";
	
	TstResInt(strlen(str1), StrLen(str1), __LINE__);
}

static void TestStrCmp()
{
	const char *s1[] ={"check", "abc", "ab"};
	const char *s2[] ={"check", "abcc", "Ab"};
	int i = 0;
	int size = 3;
	
	for (i = 0; i < size; i++)
	{
		TstResInt(strcmp(s1[i], s2[i]), StrCmp(s1[i], s2[i]), __LINE__);
	}
}

static void TestStrNCmp()
{
	const char *s1[] ={"new check", "abcddefggrr", "AB"};
	const char *s2[] ={"new check", "abcc", "BC"};
	int i = 0;
	int size = 3;
	size_t n = 4; 

	for (i = 0; i < size; i++)
	{
		TstResInt(strncmp(s1[i], s2[i], n), StrNCmp(s1[i], s2[i], n), __LINE__);
	}
}

static void TestStrCaseCmp()
{
	const char *s1[] ={"NEW", "abc", "abcd"};
	const char *s2[] ={"check", "ABC", "AbCd"};
	int i = 0;
	int size = 3;

	for (i = 0; i < size; i++)
	{
		TstResInt(strcasecmp(s1[i], s2[i]), StrCaseCmp(s1[i], s2[i]), __LINE__);
	}
}

static void TestStrCpy()
{
	const char str1[] = "Here comes the sun";
	char *str2 = NULL; 
	
	str2 = (char *)malloc(StrLen(str1) + 1); 
	if (!str2)
	{
        	printf("Memory allocation failed\n");
        	return; 
	}
	
	TstResChar(strcpy(str2, str1), StrCpy(str2, str1), __LINE__);
	
	free(str2);
	str2 = NULL;
}

static void TestStrNCpy()
{
	const char str1[] = "Here comes the sun";
	char *str2 = NULL;
	size_t n = 4; 
	
	str2 = (char *)malloc(n + 1); 
	if (!str2)
	{
        	printf("Memory allocation failed\n");
        	return; 
	}
	
	TstResChar(strncpy(str2, str1, n), StrNCpy(str2, str1, n), __LINE__);
	
	free(str2);
	str2 = NULL;
}

static void TestStrChr()
{
	const char str1[] = "Here we go again";
	int symbol = 'g';

	TstResChar(strchr(str1, symbol), StrChr(str1, symbol), __LINE__);
}

static void TestStrDup()
{
	const char str1[] = "Wait, am I the clone?";
	char *duplicated_str1 = NULL;
	
	TstResChar(strdup(str1), StrDup(str1), __LINE__);
	
	free(duplicated_str1);
	duplicated_str1 = NULL;
}

static void TestStrCat()
{
	char str1[30] = "Every beginning, ";
	const char str2[] = "Has an end";
	
	TstResChar(strcat(str1, str2), StrCat(str1, str2), __LINE__);
}

static void TestStrNCat()
{
	char str1[30] = "Every beginning, ";
	const char str2[] = "Has an end";
	size_t n = 4;
	
	TstResChar(strncat(str1, str2, n), StrNCat(str1, str2, n), __LINE__);
}

static void TestStrStr()
{
	const char str1[] = "Like looking for a needle in a haystack";
	const char str2[] = "needle";

	TstResChar(strstr(str1, str2), StrStr(str1, str2), __LINE__);
}

static void TestStrSpn()
{
	const char str1[] = "ababbcd123456abc";
	const char str2[] = "abcd";
	
	TstResInt(strspn(str1, str2), StrSpn(str1, str2), __LINE__);
}
