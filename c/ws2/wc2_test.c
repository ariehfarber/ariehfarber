/***********************************************************************************
*Auther: Arieh Farber
*Reviewr: Yarden Shai
*Date: 8/11/2023
***********************************************************************************/

#include <stdio.h>  /*printf*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc*/
#include <stddef.h> /*size_t*/
#include "wc2.h"

void TestIntSwap();
void TestCopyArray();
void TestTSizeSwap();
void TestPtrSwap();
void TestPtrSwapCombo();
void TestIsPalindrome();

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

void TestIntSwap()
{
	int x = 11;
	int y = 2785;
	
	printf("Test IntSwap\n");
	printf("Original: x=%d, y=%d\n", x, y);
	IntSwap(&x ,&y);
	printf("Swapped: x=%d, y=%d\n", x, y);
	printf("\n");
}

void TestCopyArray()
{
	int original_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	int size = sizeof(original_array) / sizeof(original_array[0]);
	int *new_array = (int *)malloc(sizeof(original_array));
	int i = 0;
	
	assert(NULL != new_array);
	
	printf("Test CopyArray\n");
	printf("Original array: ");
        for (i = 0; i < size; i++)
        {
		printf("%d ", original_array[i]);
	}
	printf("\n");
	
	CopyArray(original_array, new_array, size);
	
	printf("Copied array: ");
        for (i = 0; i < size; i++)
        {
		printf("%d ", new_array[i]);
	}
	printf("\n\n");
	
	free(new_array);
}

void TestTSizeSwap()
{
	size_t x = 55000;
	size_t y = 65000;
	
	printf("Test TSizeSwap\n");
	printf("Original: x=%lu, y=%lu\n", x, y);
	TSizeSwap(&x ,&y);
	printf("Swapped: x=%lu, y=%lu\n", x, y);
	printf("\n");
}

void TestPtrSwap()
{
	size_t x = 125000, y = 300;
	size_t *p1 = &x, *p2 = &y;
	
	printf("Test PtrSwap\n");
	printf("Original: x=%lu, y=%lu\n", *p1, *p2);
	PtrSwap(&p1 ,&p2);
	printf("Swapped: x=%lu, y=%lu\n", *p1, *p2);
	printf("\n");
}

void TestPtrSwapCombo()
{
	size_t x = 775, y = 0;
	size_t *p1 = &x, *p2 = &y;
	
	printf("Test PtrSwapCombo\n");
	printf("Original: x=%lu, y=%lu\n", *p1, *p2);
	PtrSwapCombo(&p1 ,&p2);
	printf("Swapped: x=%lu, y=%lu\n", *p1, *p2);
	printf("\n");
}

void TestIsPalindrome()
{
	char pali[] = "abcba";
	char not_pali[] = "abcabc";
	int value1 = 0;
	int value2 = 0;
	
	value1 = IsPalindrome(pali);
	value2 = IsPalindrome(not_pali);
	
	if(0 == value1)
	{
		printf(" \"%s\" is a palindrome\n", pali);
	}
	
	if(0 != value2)
	{
		printf(" \"%s\" is not a palindrome\n", not_pali);
	}
}











