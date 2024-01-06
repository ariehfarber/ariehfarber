/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Omer Bruker
*Date: 12/09/2023
*******************************************************************************/
#define _POSIX_C_SOURCE 200809L /*a macro for using strdup with c89 compiler*/

#include <stdio.h>  /*printf			  */
#include <stdlib.h> /*malloc, size_t, free*/
#include <string.h> /*strdup	  		  */

#include "ws3.h"

static void TestMatrixRowSums();
static void TestJosephusProblem();
static void TestPrintDataSize();
static void TestPrintEnvVariablesLowCase();

int main()
{
	TestMatrixRowSums();
	TestJosephusProblem();
	TestPrintDataSize();
	TestPrintEnvVariablesLowCase();
	
	return (0);
}

static void TestInt(int want, int got, int line);

static void TestMatrixRowSums() 
{
	int **array = NULL;
	int *sum_of_rows = NULL;
	int i = 0, j =0; 
	int want[COLS] = {3 , 12, 21};

	array = (int **)malloc(ROWS * sizeof(int *));
	if (NULL == array)
	{
		printf("Memory allocation failed\n");
	}
	
	for (i = 0; i < ROWS; ++i) 
	{
		array[i] = (int *)malloc(COLS * sizeof(int));
		if (NULL == array[i])
		{
			free(array);
			
			printf("Memory allocation failed\n");
		}
	}
	
	sum_of_rows = (int *)malloc(COLS * sizeof(int *));
	if (NULL == sum_of_rows)
	{
		printf("Memory allocation failed\n");
	}
	
	for (i = 0; i < ROWS; ++i)
	{
		sum_of_rows[i] = 0;
	}
		
	for (i = 0; i < ROWS; ++i)
	{
		for (j = 0; j < COLS; ++j)
		{
			array[i][j] = i * COLS + j;
		}
	}
			
	MatrixRowSums(array, sum_of_rows);
	
	for (i = 0; i < COLS; ++i)
	{
			TestInt(want[i], sum_of_rows[i], __LINE__);
	}
	
	for (i = 0; i < ROWS; ++i) 
	{
    		free(array[i]);
	}
	free(array);
	
	free(sum_of_rows);
}

static void TestJosephusProblem()
{
	size_t array[20] = {0};
	size_t index = 0;
	size_t i = 0;
	size_t size_of_array = 0;
	
	size_of_array = sizeof(array) / sizeof(array[0]); 
	
	for (i = 0; i < size_of_array; ++i) 
	{
	    array[i] = 1;
	}
	
	index = JosephusProblem(array, size_of_array);

	TestInt(8, index, __LINE__);
}

static void TestPrintDataSize()
{
	size_t i = 0;
	size_t num_of_types = 0;	
	char *types[] = {"int", "unsigned int", "int*", "int**",
        				   "float", "double", "double*", "double**",
        				   "char", "unsigned char", "size_t"};
	size_t data_size[] = {sizeof(int), sizeof(unsigned int), sizeof(int*),
        			  sizeof(int**), sizeof(float), sizeof(double),
        			  sizeof(double*), sizeof(double**), sizeof(char),
        			  sizeof(unsigned char), sizeof(size_t)}; 

	num_of_types = sizeof(data_size) / sizeof(data_size[0]);
	
	printf("\n");
	for (i = 0; i < num_of_types; ++i)
	{
		PrintDataSize(types[i], data_size[i]);
	}
	printf("\n");
}

static void TestPrintEnvVariablesLowCase()
{
	char **buffer = NULL;
	size_t environ_size = 0;
	size_t i = 0;
	
	while (NULL != environ[environ_size])
	{
		++environ_size;
	}
	
	buffer = (char **)malloc(environ_size * sizeof(char *));
	if (NULL == buffer)
	{
		printf("Memory allocation failed\n");
		return;
	}
	
	for (i = 0; i < environ_size; ++i)
	{
		buffer[i] = strdup(environ[i]);
	}
	
	PrintEnvVariablesLowCase(buffer, environ_size);
	
	for (i = 0; i < environ_size; ++i)
	{
		free(buffer[i]);
	}
	free(buffer);
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
