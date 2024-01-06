/*******************************************************************************
*Author: Arieh Farber
*Reviewer: Yarden Shai
*Date: 9/11/2023
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc*/
#include <stddef.h> /*size_t*/
#include <string.h> /*strcmp*/

#include "ws2.h"

static void TestIntSwap();
static void TestCopyArray();
static void TestTSizeSwap();
static void TestPtrSwap();
static void TestPtrSwapCombo();
static void TestIsPalindrome();

int main()
{
	TestIntSwap();
	TestCopyArray();
	TestTSizeSwap();
	TestPtrSwap();
	TestPtrSwapCombo();
	TestIsPalindrome();
	
	return (0);
}

static void TestInt(int control, int got, int line);
static void TestSizeT(size_t control, size_t got, int line);
static void TestPtr(void *control, void *got, int line);

static void TestIntSwap()
{
	int x = 11;
	int y = 2785;
	int control_x = 2785;
	int control_y = 11;
	
	IntSwap(&x ,&y);
	TestInt(control_x, x, __LINE__);
	TestInt(control_y, y, __LINE__);
}

static void TestCopyArray()
{
	int original_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	int size = 0;
	int *new_array = NULL;
	int i = 0;
	
	new_array = (int *)malloc(sizeof(original_array));
	assert(NULL != new_array);
	
	size = sizeof(original_array) / sizeof(original_array[0]);
	
	CopyArray(original_array, new_array, size);
	
	for (i = 0; i < size; ++i)
	{
		TestInt(new_array[i], original_array[i], __LINE__);
	}
	
	free(new_array);
}

static void TestTSizeSwap()
{
	size_t x = 55000;
	size_t y = 65000;
	size_t control_x = 65000;
	size_t control_y = 55000;
	
	TSizeSwap(&x ,&y);
	TestSizeT(control_x, x, __LINE__);
	TestSizeT(control_y, y, __LINE__);
}

static void TestPtrSwap()
{
	size_t x = 125000, y = 300;
	size_t *p1 = &x, *p2 = &y;
	
	PtrSwap(&p1 ,&p2);
	TestPtr(&x, p2, __LINE__);
	TestPtr(&y, p1, __LINE__);
}

static void TestPtrSwapCombo()
{
	size_t x = 775;
	size_t y = 0;
	size_t control_x = 0;
	size_t control_y = 775;
	size_t *p1 = &x, *p2 = &y;
	
	PtrSwapCombo(&p1 ,&p2);
	TestSizeT(control_x, x, __LINE__);
	TestSizeT(control_y, y, __LINE__);
}

static void TestIsPalindrome()
{
	char pali[] = "abcba";
	char not_pali[] = "abcabc";
	int value1 = 0;
	int value2 = 0;
	
	value1 = IsPalindrome(pali);
	value2 = IsPalindrome(not_pali);
	
	TestInt(1, value1, __LINE__);	
	TestInt(0, value2, __LINE__);
}

static void TestInt(int control, int got, int line)
{
	if (control != got)
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

static void TestSizeT(size_t control, size_t got, int line)
{
	if (control != got)
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

static void TestPtr(void *control, void *got, int line)
{
	if (control != got)
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
