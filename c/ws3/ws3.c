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






















