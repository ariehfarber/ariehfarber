/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Omer Bruker
*Date: 12/09/2023
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <stdlib.h> /*malloc, size_t*/

#include "ws3.h"

static void TestMatrixRowSums();
static void TestJosephusProblem();
static void TestDataSize();
static void TestPrintEnvVariablesLowCase();

int main()
{
	TestMatrixRowSums();
	TestJosephusProblem();
	TestDataSize();
	TestPrintEnvVariablesLowCase();
	
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

static void TestMatrixRowSums() 
{
	int **array = NULL;
	int *sum_of_rows = NULL;
	int i = 0, j =0; 
	int control[COLS] = {3 , 12, 21};

	array = (int **)malloc(ROWS * sizeof(int *));
	if (!array)
	{
		printf("Memory allocation failed");
	}
	
	for (i = 0; i < ROWS; i++) 
	{
		array[i] = (int *)malloc(COLS * sizeof(int));
		if (!array[i])
		{
			printf("Memory allocation failed");
		}
	}
	
	sum_of_rows = (int *)malloc(COLS * sizeof(int *));
	if (!sum_of_rows)
	{
		printf("Memory allocation failed");
	}
	
	for (i = 0; i < ROWS; i++)
	{
		sum_of_rows[i] = 0;
	}
		
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			array[i][j] = i * COLS + j;
		}
	}
			
	MatrixRowSums(array, sum_of_rows);
	
	for (i = 0; i < COLS; i++)
	{
			TstResInt(control[i], sum_of_rows[i], __LINE__);
	}
	
	for (i = 0; i < ROWS; i++) 
	{
    		free(array[i]);
	}
	free(array);
	array = NULL;
	
	free(sum_of_rows);
	sum_of_rows = NULL;
}

static void TestJosephusProblem()
{
	size_t array[20] = {0};
	size_t index = 0;
	size_t i = 0;
	size_t size_of_array = 0;
	
	size_of_array = sizeof(array) / sizeof(array[0]); 
	
	for (i = 0; i < size_of_array; i++) 
	{
	    array[i] = 1;
	}
	
	index = JosephusProblem(array, size_of_array);

	TstResInt(8, index, __LINE__);
}

static void TestDataSize()
{
	DataSize();
}

static void TestPrintEnvVariablesLowCase()
{
	PrintEnvVariablesLowCase(environ);
}
