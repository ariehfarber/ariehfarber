/***********************************************************************************
*Author: Arieh Farber 
*Reviewer:
*Date: 11/09/2023
***********************************************************************************/

#include <stdio.h>  /*printf        */
#include <assert.h> /*assert        */
#include <stddef.h> /*size_t, sizeof*/
#include <ctype.h>  /*tolower       */
#include <string.h> /*strlen, strcpy*/
#include "ws3.h"

/**********************************************************************************/
/*Exercise 1a: Ways of writing a function signature for two-dimensional array.    */
/**********************************************************************************/
/*Using fixed dimensions*/
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

/**********************************************************************************/
/*Help functions for Exercise 4*/
/**********************************************************************************/
char *StrDup(const char *str)
{
	char *duplicated = NULL;
	
	assert(NULL != str);
	
	duplicated = (char *)malloc(strlen(str) + 1);
	assert(NULL != duplicated);
	
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

/**********************************************************************************/
/*Exercise 1*/
/**********************************************************************************/
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

/**********************************************************************************/
/*Exercise 3*/
/**********************************************************************************/
void DataSize(size_t num_types, const char *types[], size_t sizes[])
{
	size_t i = 0;
	
	assert(types);
	
	for(i = 0; i < num_types; i++)
	{
		printf("The size of %s is %lu byts\n", types[i], sizes[i]);
	}
	printf("\n");
}

/**********************************************************************************/
/*Exercise 4*/
/**********************************************************************************/
void PrintEnvVariables(char **buffer,size_t size)
{
	size_t i = 0;
	
	assert(buffer);
	
	printf("Environment variables");
	for(i = 0; i < size; i++)
	{
		printf("%s\n", ToLowerString(buffer[i]));
	}
	printf("\n");
}

/**********************************************************************************/
/*Exercise 2*/
/**********************************************************************************/
size_t JosephusProblem(unsigned int size)
{
	size_t n = 0;
	size_t index = 0;
	size_t power_of_two = 2;
	
	if(size <= 2)
	{
	return (0);
	}
	
	while(power_of_two < size)
	{
		power_of_two *= 2;
		n++;
	}
	
	index = (size % (power_of_two / 2)) * 2;
	
	return (index);	
}

























































