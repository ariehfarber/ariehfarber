/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Omer Bruker
*Date: 12/09/2023
*******************************************************************************/
#include <stdio.h>  /*printf        */
#include <assert.h> /*assert        */
#include <stddef.h> /*size_t 		*/
#include <ctype.h>  /*tolower       */

#include "ws3.h"

#define ERROR -1
#define TRUE 1
#define FALSE 0

static char *ToLowerString(char *str);

int *MatrixRowSums(int **matrix, int *row_sums)
{
	int i = 0, j = 0;
	
	assert(matrix);
	assert(row_sums);
	
	for (i = 0; i < ROWS; ++i)
	{
		for (j = 0; j < COLS; ++j)
		{
			*row_sums += matrix[i][j];
		}
		++row_sums;
	}
	
	return (row_sums); 
}

size_t JosephusProblem(size_t *array, size_t array_size)
{
	size_t i = 0;
	size_t is_alive = FALSE;
	size_t survivors = array_size;
	
	while (1 < survivors)
	{
		if (1 == array[i])
		{
		    if (TRUE == is_alive)
		    {
		        array[i] = 0; 
		        survivors--;
		        is_alive = FALSE;
		    }
		    else
		    {
		        is_alive = TRUE; 
		    }
		}
        i = (i + 1) % array_size;
		while (0 == array[i] && 1 < survivors)
		{
			i = (i + 1) % array_size;
		}
	}
	
    for (i = 0; i < array_size; ++i) 
    {
    	if (1 == array[i]) 
    	{
            return (i);
        }
    }
    
    return (ERROR);
}

void PrintDataSize(char *type, size_t size)
{	
	printf("The size of %s is %lu byts\n", type, size);
}

void PrintEnvVariablesLowCase(char **buffer, size_t environ_size)
{
	size_t i = 0;
	
	assert(buffer);
		
	printf("Environment variables\n");
	for (i = 0; i < environ_size; ++i)
	{
		printf("%s\n", ToLowerString(buffer[i]));
	}
	printf("\n");
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
	++str;
	}
	
	return (start);
}
