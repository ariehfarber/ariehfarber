/*******************************************************************************
*Auther: Arieh Farber
*******************************************************************************/
#include "Quiz10.h"

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
	int array[8] = {-2, 1, -3, 4, -1, 2, 3, -5, 4};
	int size = 0;
	int *max; 
	int *index_i; 
	int *index_j;
	int control[3] = {8, 3, 6};
	int i = 0;
	
	size = sizeof(array) / sizeof(array[0]);
	
	MaxSubArray(array, size, max, index_i, index_j);
	
	TstResInt(control[0], *max, __LINE__);
	TstResInt(control[1], *index_i, __LINE__);
	TstResInt(control[2], *index_j, __LINE__);
}


