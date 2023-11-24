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

int *MatrixRowSums(int **matrix, int *row_sums)
{
	int i = 0, j = 0;
	
	assert(matrix);
	assert(row_sums);
	
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			*row_sums += matrix[i][j];
		}
		row_sums++;
	}
	
	return (row_sums); 
}

size_t JosephusProblem(size_t *array, size_t array_size)
{
	size_t i = 0;
	size_t kill_check = 0;
	size_t survivors = array_size;
	
	while (survivors > 1)
	{
		if (array[i] == 1)
		{
		    if (kill_check == 1)
		    {
		        array[i] = 0; 
		        survivors--;
		        kill_check = 0;
		    }
		    else
		    {
		        kill_check = 1; 
		    }
		}
        i = (i + 1) % array_size;
		while (0 == array[i] && survivors > 1)
		{
			i = (i + 1) % array_size;
		}
	}
	
    for (i = 0; i < array_size; i++) 
    {
    	if (array[i] == 1) 
    	{
            return (i);
        }
    }
    
    return (-1);
}

void DataSize()
{
	size_t i = 0;
	size_t num_types = 0;
	
	size_t sizes[] = {sizeof(int), sizeof(unsigned int), sizeof(int*),
        			  sizeof(int**), sizeof(float), sizeof(double),
        			  sizeof(double*), sizeof(double**), sizeof(char),
        			  sizeof(unsigned char), sizeof(size_t)};
        
	const char *types[] = {"int", "unsigned int", "int*", "int**",
        				   "float", "double", "double*", "double**",
        				   "char", "unsigned char", "size_t"};
	
	num_types = sizeof(sizes) / sizeof(sizes[0]);
		
	for (i = 0; i < num_types; i++)
	{
		printf("The size of %s is %lu byts\n", types[i], sizes[i]);
	}
	printf("\n");
}

static char *StrDup(const char *str)
{
	char *duplicated = NULL;
	
	assert(NULL != str);
	
	duplicated = (char *)malloc(strlen(str) + 1);
	if (!duplicated)
	{
		return (NULL);
	}
	
	duplicated = strcpy(duplicated ,str);
	
	return (duplicated);
}

static char *ToLowerString(char *str)
{
	char *start = NULL;
	
	assert(NULL != str);
	
	start = str;
		
	while ('\0' != *str)
	{
		if (*str >= 'A' && *str <= 'Z')
		{
			*str = tolower(*str);
		}
	str++;
	}
	
	return (start);
}

void PrintEnvVariablesLowCase(char **env_var)
{
	char **buffer = NULL;
	size_t size = 0;
	size_t i = 0;
	
	assert(env_var);
	
	while (NULL != env_var[size])
	{
		size++;
	}
	
	buffer = (char **)malloc(size * sizeof(char *));
	if (!buffer)
	{
		printf("Memory allocation failed");
		return;
	}
	
	for (i = 0; i < size; i++)
	{
		buffer[i] = StrDup(environ[i]);
	}

	printf("Environment variables");
	for (i = 0; i < size; i++)
	{
		printf("%s\n", ToLowerString(buffer[i]));
	}
	printf("\n");
	
	/*Freeing memory*/
	for (i = 0; i < size; i++)
	{
		free(buffer[i]);
	}
	free(buffer);
	buffer = NULL;
}
