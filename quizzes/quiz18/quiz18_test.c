/*******************************************************************************
*Auther: Arieh Farber
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <stddef.h> /*size_t*/

#include "quiz18.h"

static void TestSumIntPairsToLongs();

int main()
{
	TestSumIntPairsToLongs();
	
	return (0);
}

static void TestSumIntPairsToLongs()
{
	long *arr_long = NULL;
	int ints[] = {1, 6, 456, -3, 8, 12, 461168060, 461106860};
	size_t num_of_elements = 0;
	size_t i = 0;
	
	num_of_elements = sizeof(ints) / sizeof(ints[0]);
	
	arr_long = SumIntPairsToLongs(ints, num_of_elements);
	
	for (i = 0; i < (num_of_elements / 2); i++)
	{
		printf("%lu\n", arr_long[i]);
	}
}

  


