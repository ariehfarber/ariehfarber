/*******************************************************************************
*Auther: Arieh Farber
*******************************************************************************/
#include "quiz17.h"

int FindNumInArr(int arr[], int n, int size)
{
	int i = 0;
	
	while (0 != (arr[i] - n) && size != i)
	{
		i++;
	}
	
	return (i != size);
}
