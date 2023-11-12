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

void AllOneArray(int array[ROWS][COLS]);

void AllTwoArray(int array[][COLS], int rows);

void AllThreeArray(int *arr, int rows, int cols);

void AllFourArray(int (*array)[COLS], int rows);

void AllFiveArray(int **array, int rows, int cols);

char *StrDup(const char *str);

int *MatrixRowSums(int **matrix, int *rows_sums);

void DataSize(size_t num_types, const char *types[], size_t sizes[]);

void PrintEnvVariables(char **buffer,size_t size);

size_t JosephusProblem(unsigned int size);

#endif /*  __WS3_H__ */
