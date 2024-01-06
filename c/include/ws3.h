/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Omer Bruker
*Date: 12/09/2023
*******************************************************************************/
#ifndef  __WS3_H__
#define __WS3_H__

#include <stddef.h> /*size_t*/
#include <stdlib.h> /*environ*/

extern char **environ;
#define ROWS 3 
#define COLS 3

/*******************************************************************************
*Description: Calculates the sum of each row in a matrix.
*******************************************************************************/
int *MatrixRowSums(int **matrix, int *rows_sums);

/*******************************************************************************
*Description: Calculates the index of the last soldier standing
*			  in Josephus Problem. 
*******************************************************************************/
size_t JosephusProblem(size_t *array, size_t array_size);

/*******************************************************************************
*Description: Prints the size of each data type.
*******************************************************************************/
void PrintDataSize(char *type, size_t size);

/*******************************************************************************
*Description: Copies the environment variables in lower case.
*******************************************************************************/
void PrintEnvVariablesLowCase(char **buffer, size_t environ_size);

#endif /*__WS3_H__*/











