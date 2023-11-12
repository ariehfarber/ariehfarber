/***********************************************************************************
*Author: Arieh Farber
*Reviewer:
*Date: 11/09/2023
***********************************************************************************/

#ifndef  __WS3_H__
#define __WS3_H__

#include <stddef.h> /*size_t*/
#include <stdlib.h> /*environ*/

extern char **environ;
#define ROWS 3 
#define COLS 3

/***********************************************************************************
*Description: five ways of writing a function signature which accepts
*	      a two-dimensional array
***********************************************************************************/
void AllOneArray(int array[ROWS][COLS]);
void AllTwoArray(int array[][COLS], int rows);
void AllThreeArray(int *arr, int rows, int cols);
void AllFourArray(int (*array)[COLS], int rows);
void AllFiveArray(int **array, int rows, int cols);


char *StrDup(const char *str);

/***********************************************************************************
*Description: Calculates the sum of each row in a matrix
***********************************************************************************/
int *MatrixRowSums(int **matrix, int *rows_sums);

/***********************************************************************************
*Description: prints the size of each data type
***********************************************************************************/
void DataSize(size_t num_types, const char *types[], size_t sizes[]);

/***********************************************************************************
*Description: prints the environment variables in lower case
***********************************************************************************/
void PrintEnvVariables(char **buffer,size_t size);

/***********************************************************************************
*Description: Calculates the index of the last soldier standing in Josephus Problem 
***********************************************************************************/
size_t JosephusProblem(unsigned int size);

#endif /*__WS3_H__*/










