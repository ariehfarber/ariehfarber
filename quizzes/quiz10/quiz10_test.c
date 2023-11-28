/*******************************************************************************
*Auther: Arieh Farber
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <stdlib.h> /*malloc*/
#include "quiz10.h"

static void TestMaxSubArray();

int main()
{
	TestMaxSubArray();
	
	return (0);
}

static void TstResInt(int control, int func_res, int line)
{
	if (control != func_res)
	{
		printf("\033[0;31m");
		printf("Error. failed at line %d\n", line);
		printf("\033[0m"); 
	}
}

static void TestMaxSubArray()
{
	int array[9] = {-2, 1, -3, 4, -1, 2, 3, -5, 4};
	int array_size = 0;
	int control_size = 0;
	int *buffer = NULL;
	int control[3] = {8, 3, 6};
	
	array_size = sizeof(array) / sizeof(array[0]);
	control_size = sizeof(control) / sizeof(control[0]);
	
	buffer = (int *)malloc(control_size);
	
	buffer = MaxSubArray(array, array_size, buffer);
	
	TstResInt(control[0], buffer[0], __LINE__);
	TstResInt(control[1], buffer[1], __LINE__);
	TstResInt(control[2], buffer[2], __LINE__);
	
	free(buffer);
	buffer = NULL;
}


