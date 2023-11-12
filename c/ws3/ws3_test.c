/***********************************************************************************
*Author: Arieh Farber
*Reviewer:
*Date: 11/09/2023
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
void TestPrintEnvVariables();

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
	TestPrintEnvVariables();
	
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

	for (i = 0; i < rows; i++) 
	{
		array[i] = (int *)malloc(cols * sizeof(int));
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
	assert(array);
	for (i = 0; i < ROWS; i++) 
	{
		array[i] = (int *)malloc(COLS * sizeof(int));
		assert(array[i]);
	}
	
	/*Allocating memory for 1D array*/
	sum_of_rows = (int *)malloc(COLS * sizeof(int *));
	assert(sum_of_rows);
	
	/*Assigning matrix values*/
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
	unsigned int size;
	size_t index = 0;
	
	size = 16;
	
	index = JosephusProblem(size);

	printf("The index of the last soldier is %lu\n\n", index);
}

/**********************************************************************************
Exercise 3
**********************************************************************************/
void TestDataSize()
{
	size_t num_types = 0;
	
	size_t sizes[] = {sizeof(int), sizeof(unsigned int), sizeof(int*),
        sizeof(int**), sizeof(float), sizeof(double), sizeof(double*),
        sizeof(double**), sizeof(char), sizeof(unsigned char), sizeof(size_t)};
        
	const char *types[] = {"int", "unsigned int", "int*", "int**",
        "float", "double", "double*", "double**",
        "char", "unsigned char", "size_t"};
	
	num_types = sizeof(sizes) / sizeof(sizes[0]);

	DataSize(num_types, types, sizes);
}

/**********************************************************************************
Exercise 4
**********************************************************************************/
void TestPrintEnvVariables()
{
	char **buffer = NULL;
	size_t size = 0;
	size_t i = 0;
	
	while(NULL != environ[size])
	{
		size++;
	}
	
	buffer = (char **)malloc(size * sizeof(char *));
	assert(buffer);
	
	for(i = 0; i < size; i++)
	{
		buffer[i] = DtrDup(environ[i]);
	}
	
	PrintEnvVariables(buffer, size);
	
	free(buffer);
	buffer = NULL;
}




































