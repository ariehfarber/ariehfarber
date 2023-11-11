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


void TestMatrixRowSums();
void TestDataSize();
void TestPrintEnvVariables();

int main()
{
	TestMatrixRowSums();
	TestDataSize();
	TestPrintEnvVariables();
	
	return (0);
}

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
		buffer[i] = StrDup(environ[i]);
	}
	
	PrintEnvVariables(buffer, size);
	
	free(buffer);
	buffer = NULL;
}



































