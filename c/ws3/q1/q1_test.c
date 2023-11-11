/***********************************************************************************
*Author: Arieh Farber
*Date: 11/09/2023
***********************************************************************************/

#include <stdio.h>  /*printf*/
#include <stdlib.h> /*malloc*/
#include "ws3.h"

void TestAllOneArray();
void TestAllTwoArray();
void TestAllThreeArray();
void TestAllFourArray();
void TestAllFiveArray();

int main()
{
	TestAllOneArray();
	TestAllTwoArray();
	TestAllThreeArray();
	TestAllFourArray();
	TestAllFiveArray();
	
	return (0);
}

void TestAllOneArray()
{
	int array[ROWS][COLS] = {0};
	int i = 0, j = 0;
		
	AllOneArray(array);
	
	printf("Test AllOneArray:\n");
	for(i = 0; i < ROWS; i++)
	{
		for(j = 0; j < COLS; j++)
		{
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void TestAllTwoArray()
{
	int array[6][COLS] = {0};
	int i = 0, j = 0;
	int rows = 6;
		
	AllTwoArray(array, rows);
	
	printf("Test AllTwoArray:\n");
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < COLS; j++)
		{
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void TestAllThreeArray() 
{
	int array[6][6] = {0};
	int i = 0, j = 0;
	int rows = 6, columns = 6;
		
	AllThreeArray((int *)array, rows, columns);
	
	printf("Test AllThreeArray:\n");
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < columns; j++)
		{
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void TestAllFourArray() 
{
	int array[3][COLS] = {0};
	int i = 0, j = 0;
	int rows = 3;
		
	AllFourArray(array, rows);
	
	printf("Test AllFourArray:\n");
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < COLS; j++)
		{
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void TestAllFiveArray() 
{
	int **array;
	int rows = 2; 
	int cols = 2;
	int i = 0 , j = 0; 

	array = (int **)malloc(rows * sizeof(int *));

	for (i = 0; i < rows; i++) 
	{
		array[i] = (int *)malloc(cols * sizeof(int));
	}
	
	AllFiveArray(array, rows, cols);
	
	printf("Test AllFiveArray:\n");
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	for (i = 0; i < rows; i++) 
	{
    		free(array[i]);
	}
	free(array);
}







































