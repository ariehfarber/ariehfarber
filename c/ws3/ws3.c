/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Omer Bruker
*Date: 12/09/2023
*******************************************************************************/

#include <stdio.h>  /*printf        */
#include <assert.h> /*assert        */
#include <stddef.h> /*size_t, sizeof*/
#include <ctype.h>  /*tolower       */
#include <string.h> /*strlen, strcpy*/

#include "ws3.h"

/*******************************************************************************
*Exercise 1a: Ways of writing a function signature for two-dimensional array. 
*	      Using fixed dimensions
*******************************************************************************/
void AllOneArray(int array[ROWS][COLS])
{
	int i = 0, j = 0;
	
	for(i = 0; i < ROWS; i++)
	{
		for(j = 0; j < COLS; j++)
		{
			array[i][j] = 1;
		}
	}
}

void AllTwoArray(int array[][COLS], int rows)
{
	int i = 0, j = 0;
	
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < COLS; j++)
		{
			array[i][j] = 2;
		}
	}
}

/*Using a Single Pointer*/
void AllThreeArray(int *array, int rows, int cols) 
{
	int i = 0, j = 0;
	
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			array[i * cols + j] = 3;
		}
	}   
}

/*Using a Pointer to an Array of Fixed Size*/
void AllFourArray(int (*array)[COLS], int rows) 
{
	int i = 0, j = 0;
	
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < COLS; j++)
		{
			array[i][j] = 4;
		}
	}  
}

/*Using a Double Pointer*/
void AllFiveArray(int **array, int rows, int cols) 
{
	int i = 0, j = 0;
	
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			array[i][j] = 5;
		}
	} 
}

/*******************************************************************************
*Exercise 1
*******************************************************************************/
int *MatrixRowSums(int **matrix, int *row_sums)
{
	int i = 0, j = 0;
	
	assert(matrix);
	assert(row_sums);
	
	
	for(i = 0; i < ROWS; i++)
	{
		for(j = 0; j < COLS; j++)
		{
			*row_sums += matrix[i][j];
		}
		row_sums++;
	}
	
	return(row_sums); 
}

/*******************************************************************************
*Exercise 2
*******************************************************************************/
size_t JosephusProblem(size_t *array)
{
	size_t i = 0;
	size_t power_of_two = 4;
	size_t size = 0;
	
	while('\0' != array[size])
	{
		size++;
	}
	
	if(size <= 2)
	{
		return (0);
	}
	
	if(size == 3)
	{
		return (2);
	}
	
	while(power_of_two < size)
	{
		power_of_two *= 2;
	}
	
	i = (2 * size) % power_of_two;
	
	return (i);	
}

/*******************************************************************************
*Exercise 3
*******************************************************************************/
void DataSize()
{
	size_t i = 0;
	size_t num_types = 0;
	
	size_t sizes[] = {sizeof(int), sizeof(unsigned int), sizeof(int*),
        sizeof(int**), sizeof(float), sizeof(double), sizeof(double*),
        sizeof(double**), sizeof(char), sizeof(unsigned char), sizeof(size_t)};
        
	const char *types[] = {"int", "unsigned int", "int*", "int**",
        "float", "double", "double*", "double**",
        "char", "unsigned char", "size_t"};
	
	num_types = sizeof(sizes) / sizeof(sizes[0]);
		
	for(i = 0; i < num_types; i++)
	{
		printf("The size of %s is %lu byts\n", types[i], sizes[i]);
	}
	printf("\n");
}

/*******************************************************************************
*Help functions for Exercise 4
*******************************************************************************/
char *StrDup(const char *str)
{
	char *duplicated = NULL;
	
	assert(NULL != str);
	
	duplicated = (char *)malloc(strlen(str) + 1);
	if(!duplicated)
	{
		return NULL;
	}
	
	duplicated = strcpy(duplicated ,str);
	
	return (duplicated);
}

char *ToLowerString(char *str)
{
	char *start = NULL;
	
	assert(NULL != str);
	
	start = str;
		
	while('\0' != *str)
	{
		if(*str >= 'A' && *str <= 'Z')
		{
			*str = tolower(*str);
		}
	str++;
	}
	
	return(start);
}

/*******************************************************************************
*Exercise 4
*******************************************************************************/
void PrintEnvVariablesLowCase(const char **env_var)
{
	char **buffer = NULL;
	size_t size = 0;
	size_t i = 0;
	
	assert(env_var);
	
	while(NULL != env_var[size])
	{
		size++;
	}
	
	buffer = (char **)malloc(size * sizeof(char *));
	if(!buffer)
	{
		printf("Memory allocation failed");
		return;
	}
	
	for(i = 0; i < size; i++)
	{
		buffer[i] = StrDup(environ[i]);
	}

	printf("Environment variables");
	for(i = 0; i < size; i++)
	{
		printf("%s\n", ToLowerString(buffer[i]));
	}
	printf("\n");
	
	/*Freeing memory*/
	for(i = 0; i < size; i++)
	{
		free(buffer[i]);
	}
	free(buffer);
	buffer = NULL;
}


























































