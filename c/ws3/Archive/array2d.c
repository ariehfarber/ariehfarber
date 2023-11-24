/*******************************************************************************
*Author: Arieh Farber 
*Date: 12/09/2023
*******************************************************************************/
#include "array2d.h"

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
