/***********************************************************************************
*Author: Arieh Farber
*Date: 11/09/2023
***********************************************************************************/

#include <stdio.h> /*printf*/
#include "ws3.h"

/*Using fixed dimensions - When both dimensions are available globally*/
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

/*Using fixed dimensions - When the second dimension is available globally*/
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

/*Using a Double Pointer (for Dynamic Arrays)*/
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
























