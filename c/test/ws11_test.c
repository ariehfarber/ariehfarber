/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Yarden Shai
*Date: 28/11/2023
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <stdlib.h> /*atoi  */
#include <string.h> /*strcmp*/

#include "ws11.h"

#define TRUE 1

static void TestAtoi();
static void	TestAtoiAnyBase();
static void TestItoa();
static void	TestItoaAnyBase();
static void TestPrintArrayOfChars();
static void TestIsLittleEndian();

int main()
{
	TestAtoi();
	TestAtoiAnyBase();
	TestItoa();
	TestItoaAnyBase();
	TestPrintArrayOfChars();
	TestIsLittleEndian();
	
	return (0);
}

static void TestInt(int want, int got, int line);
static void TestChar(char *want, char *got, int line);

static void TestAtoi()
{
	int got_num = 0;
	int want_num = 0;
	char *got_string = " 	-223";
	
	got_num = Atoi(got_string);
	want_num = atoi(got_string);
	
	TestInt(want_num, got_num, __LINE__);
}

static void	TestAtoiAnyBase()
{
	int got_num = 0;
	int want_num = 10;
	char *got_string = "10";
	int base = 10;
	
	got_num = AtoiAnyBase(got_string, base);
	
	TestInt(want_num, got_num, __LINE__);
}

static void TestItoa()
{
	int num = 0;
	char *want_str = "0";
	char *str_buffer = NULL;
	
	str_buffer = (char *)malloc(strlen(want_str) + 1);
	
	Itoa(num, str_buffer);
	
	TestChar(want_str, str_buffer, __LINE__);
	
	free(str_buffer);
	str_buffer = NULL;
}

static void	TestItoaAnyBase()
{
	int got_num = -1000;
	char *str_buffer = NULL;
	char *want_str = "-RS";
	int base = 36;
	
	str_buffer = (char *)malloc(strlen(want_str) + 1);
	
	ItoaAnyBase(got_num, str_buffer, base);
	
	TestChar(want_str, str_buffer, __LINE__);
	
	free(str_buffer);
	str_buffer = NULL;
}

static void TestPrintArrayOfChars()
{
    char array1[] = {'A', 'A', 'a'};
    char array2[] = {'A', 'a', 'f', 'f', 'f', 'f', 'f'};
    char array3[] = {'g', 'g', 'g', 'N', 'g'};
	size_t size1 = 0;
	size_t size2 = 0;
	size_t size3 = 0;
	
	size1 = sizeof(array1) / sizeof(array1[0]);
	size2 = sizeof(array2) / sizeof(array2[0]);
	size3 = sizeof(array3) / sizeof(array3[0]);
	
	PrintArrayOfChars(array1, array2 ,array3, size1, size2, size3);
}

static void TestIsLittleEndian()
{
	TestInt(TRUE, IsLittleEndian(), __LINE__);
	
	TestInt(TRUE, IS_LITTLE_ENDIAN, __LINE__);
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
