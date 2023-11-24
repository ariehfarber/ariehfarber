/*******************************************************************************
*Author: Arieh Farber 
*Date: 12/09/2023
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <stdlib.h> /*malloc*/

#include "array2d.h"

static void TestAllOneArray();
static void TestAllTwoArray();
static void TestAllThreeArray();
static void TestAllFourArray();
static void TestAllFiveArray();

int main()
{
	TestAllOneArray();
	TestAllTwoArray();
	TestAllThreeArray();
	TestAllFourArray();
	TestAllFiveArray();	
	
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

static void TestAllOneArray()
{
	int array[ROWS][COLS] = {0};
	int i = 0, j = 0;
		
	AllOneArray(array);
	
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			TstResInt(1, array[i][j], __LINE__);
		}
	}
}

static void TestAllTwoArray()
{
	int array[6][COLS] = {0};
	int i = 0, j = 0;
	int rows = 6;
		
	AllTwoArray(array, rows);
	
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			TstResInt(2, array[i][j], __LINE__);
		}
	}
}

static void TestAllThreeArray() 
{
	int array[6][6] = {0};
	int i = 0, j = 0;
	int rows = 6, columns = 6;
		
	AllThreeArray((int *)array, rows, columns);
	
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			TstResInt(3, array[i][j], __LINE__);
		}
	}
}

static void TestAllFourArray() 
{
	int array[3][COLS] = {0};
	int i = 0, j = 0;
	int rows = 3;
		
	AllFourArray(array, rows);
	
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			TstResInt(4, array[i][j], __LINE__);
		}
	}
}

static void TestAllFiveArray() 
{
	int **array;
	int rows = 2; 
	int cols = 2;
	int i = 0 , j = 0; 

	array = (int **)malloc(rows * sizeof(int *));
	if (!array)
	{
		printf("Memory allocation failed");
	}

	for (i = 0; i < rows; i++) 
	{
		array[i] = (int *)malloc(cols * sizeof(int));
		if (!array[i])
		{
			printf("Memory allocation failed");
		}
	}
	
	AllFiveArray(array, rows, cols);
	
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			TstResInt(5, array[i][j], __LINE__);
		}
	}
	
	for (i = 0; i < rows; i++) 
	{
    		free(array[i]);
	}
	free(array);
}
