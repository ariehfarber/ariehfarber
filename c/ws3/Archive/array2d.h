/*******************************************************************************
*Author: Arieh Farber 
*Date: 12/09/2023
*******************************************************************************/
#ifndef  __ARRAY2D_H__
#define __ARRAY2D_H__

#include <stddef.h> /*size_t*/

#define ROWS 3 
#define COLS 3

/*******************************************************************************
*Description: Five ways of writing a function signature which accepts a two-
*			  dimensional array: 
*								- Using a simple decleration with both indexs 
*								- Using a simple decleration with one index
*								- Using a Single Pointer
*								- Using a Pointer to an Array of Fixed Size
*								- Using a Double Pointer		
*******************************************************************************/
void AllOneArray(int array[ROWS][COLS]);
void AllTwoArray(int array[][COLS], int rows);
void AllThreeArray(int *arr, int rows, int cols);
void AllFourArray(int (*array)[COLS], int rows);
void AllFiveArray(int **array, int rows, int cols);

#endif /*__ARRAY2D_H__*/
