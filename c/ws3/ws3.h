/***********************************************************************************
*Author: Arieh Farber
*Reviewer:
*Date: 11/09/2023
***********************************************************************************/

#ifndef  __WS3_H__
#define __WS3_H__

#include <stddef.h> /*size_t*/
#include <stdlib.h> /*environ*/

/*Global variables*/
extern char **environ;

/*Macro variables*/
#define ROWS 3 
#define COLS 3

/*Functions*/
char *StrDup(const char *str);

int *MatrixRowSums(int **matrix, int *rows_sums);

void DataSize(size_t num_types, const char *types[], size_t sizes[]);

void PrintEnvVariables(char **buffer,size_t size);

#endif /*  __WS3_H__ */
