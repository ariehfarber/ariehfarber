/***********************************************************************************
*Author: Arieh Farber 
*Reviewer: Omer Bruker
*Date: 12/09/2023
***********************************************************************************/

#include <stdio.h>  /*printf*/
#include <stdlib.h> /*malloc*/
#include <string.h> /*strlen*/
#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/

#include "ws3.h"

void TestAllOneArray();
void TestAllTwoArray();
void TestAllThreeArray();
void TestAllFourArray();
void TestAllFiveArray();
void TestMatrixRowSums();
void TestJosephusProblem();
void TestDataSize();
void TestCpyEnvVariables();

int main()
{
	TestAllOneArray();
	TestAllTwoArray();
	TestAllThreeArray();
	TestAllFourArray();
	TestAllFiveArray();	
	TestMatrixRowSums();
	TestJosephusProblem();
	TestDataSize();
	TestCpyEnvVariables();
	
	return (0);
}

/**********************************************************************************
Exercise 1a: Ways of writing a function signature for two-dimensional array.
**********************************************************************************/
void TestAllOneArray()
{
	int array[ROWS][COLS] = {0};
	int i = 0, j = 0;
		
	AllOneArray(array);
	
	printf("Test AllOneArray:\n");
	for(i = 0; i < ROWS; i++)
	{
		for(j = 0; j < COLS; j++)
		{
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void TestAllTwoArray()
{
	int array[6][COLS] = {0};
	int i = 0, j = 0;
	int rows = 6;
		
	AllTwoArray(array, rows);
	
	printf("Test AllTwoArray:\n");
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < COLS; j++)
		{
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void TestAllThreeArray() 
{
	int array[6][6] = {0};
	int i = 0, j = 0;
	int rows = 6, columns = 6;
		
	AllThreeArray((int *)array, rows, columns);
	
	printf("Test AllThreeArray:\n");
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < columns; j++)
		{
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void TestAllFourArray() 
{
	int array[3][COLS] = {0};
	int i = 0, j = 0;
	int rows = 3;
		
	AllFourArray(array, rows);
	
	printf("Test AllFourArray:\n");
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < COLS; j++)
		{
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void TestAllFiveArray() 
{
	int **array;
	int rows = 2; 
	int cols = 2;
	int i = 0 , j = 0; 

	array = (int **)malloc(rows * sizeof(int *));
	if(!array)
	{
		printf("Memory allocation failed");
	}

	for (i = 0; i < rows; i++) 
	{
		array[i] = (int *)malloc(cols * sizeof(int));
		if(!array[i])
		{
			printf("Memory allocation failed");
		}
	}
	
	AllFiveArray(array, rows, cols);
	
	printf("Test AllFiveArray:\n");
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	for (i = 0; i < rows; i++) 
	{
    		free(array[i]);
	}
	free(array);
}

/**********************************************************************************
Exercise 1
**********************************************************************************/
void TestMatrixRowSums() 
{
	int **array = NULL;
	int *sum_of_rows = NULL;
	int i = 0, j =0; 

	/*Allocating memory for 2D array*/
	array = (int **)malloc(ROWS * sizeof(int *));
	if(!array)
	{
		printf("Memory allocation failed");
	}
	
	for (i = 0; i < ROWS; i++) 
	{
		array[i] = (int *)malloc(COLS * sizeof(int));
		if(!array[i])
		{
			printf("Memory allocation failed");
		}
	}
	
	/*Allocating memory for 1D array*/
	sum_of_rows = (int *)malloc(COLS * sizeof(int *));
	if(!sum_of_rows)
	{
		printf("Memory allocation failed");
	}
	
	/*Assigning matrix values*/
	for(i = 0; i < ROWS; i++)
	{
		sum_of_rows[i] = 0;
	}
		
	for(i = 0; i < ROWS; i++)
	{
		for(j = 0; j < COLS; j++)
		{
			array[i][j] = i * COLS + j;
		}
	}
	
	/*Printing original matrix*/
	printf("The matrix:\n");
	for(i = 0; i < ROWS; i++)
	{
		for(j = 0; j < COLS; j++)
		{
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}
		
	MatrixRowSums(array, sum_of_rows);
	
	printf("The matrix rows sum:\n");
	for(i = 0; i < COLS; i++)
	{
			printf("%d\n", sum_of_rows[i]);
	}
	printf("\n");
	
	/*Freeing memory of 2D array*/
	for (i = 0; i < ROWS; i++) 
	{
    		free(array[i]);
	}
	free(array);
	array = NULL;
	
	/*Freeing memory of 1D array*/
	free(sum_of_rows);
	sum_of_rows = NULL;
}

/**********************************************************************************
Exercise 2
**********************************************************************************/
void TestJosephusProblem()
{
	size_t array[101] = {0};
	size_t index = 0;
	size_t i = 0;
	
	for (i = 0; i < 100; i++) 
	{
	    array[i] = 1;
	}
	
	index = JosephusProblem(array);

	printf("The index of the last soldier is %lu\n\n", index);
}

/**********************************************************************************
Exercise 3
**********************************************************************************/
void TestDataSize()
{
	DataSize();
}

/**********************************************************************************
Exercise 4
**********************************************************************************/
void TestCpyEnvVariables()
{
	CpyEnvVariables(environ);
}




































