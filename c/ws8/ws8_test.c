/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Dvir Monajem
*Date: 22/11/2023
*******************************************************************************/
#include <stdio.h>  /*printf	   */
#include <stdlib.h> /*size_t,malloc*/
#include <assert.h> /*assert	   */
#include <string.h> /*strlen	   */

#include "ws8.h"

#define ARRAY_NUM 3

#define MAX2(a, b) ((a > b) ? a : b)

#define MAX3(a, b, c) ( (a > b && a > c) ? a : ( b > c) ? b : c )  

#define SIZEOF_VAR(a) ((size_t)(&a + 1)-(size_t)(&a)) 

#define SIZEOF_TYPE(type) ((size_t)((char *)(&((type *)0)[1]) - \
			 			  (char *)((type *)0)))

static void TestStructElements();
static void TestMax2();
static void TestMax3();
static void TestSizeOfVar();
static void TestSizeOfType();

int main()
{
	TestStructElements();
	TestMax2();
	TestMax3();
	TestSizeOfVar();
	TestSizeOfType();
	
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

static void TestStructElements()
{
	int num = 10;
	char *string = NULL;
	element_t element_array[ELEMENT_NUM];
	
	string =  malloc(sizeof(char *) * strlen("chapter") + 1);
	assert(string);
	
    strcpy(string, "chapter");

	SetFloat(&element_array[0], 4.2);
	SetInt(&element_array[1], 500);
	SetInt(&element_array[2], 12);
	SetFloat(&element_array[3], 56.3);
	SetString(&element_array[4], string);

	PrintElements(element_array);
	
	AddElements(element_array, num);
	
	PrintElements(element_array);
	
	CleanElements(element_array);
}

static void TestMax2()
{
	int i = 0;
	int array_a[ARRAY_NUM] = {10, 58, -6}; 
	int array_b[ARRAY_NUM] = {89, 0, -50};
	int array_res[ARRAY_NUM] = {0, 0, 0};
	int array_control[ARRAY_NUM] = {89, 58, -6};
	
	for (i = 0; i < ARRAY_NUM; i++)
	{
		array_res[i] = MAX2(array_a[i], array_b[i]);
		TstResInt(array_control[i], array_res[i], __LINE__);	
	}
}

static void TestMax3()
{
	int i = 0;
	int array_a[ARRAY_NUM] = {10, 58, -6}; 
	int array_b[ARRAY_NUM] = {89, 0, -50};
	int array_c[ARRAY_NUM] = {365, -8, 3};
	int array_res[ARRAY_NUM] = {0, 0, 0};
	int array_control[ARRAY_NUM] = {365, 58, 3};
	
	for (i = 0; i < ARRAY_NUM; i++)
	{
		array_res[i] = MAX3(array_a[i], array_b[i], array_c[i]);
		TstResInt(array_control[i], array_res[i], __LINE__);	
	}
}

static void TestSizeOfVar()
{
	int x = 0; 
	long y = 0; 
		
	TstResInt(sizeof(x), SIZEOF_VAR(x), __LINE__);	
	TstResInt(sizeof(y), SIZEOF_VAR(y), __LINE__);
}

static void TestSizeOfType()
{
	TstResInt(sizeof(long), SIZEOF_TYPE(long), __LINE__);	
	TstResInt(sizeof(char), SIZEOF_TYPE(char), __LINE__);
}








