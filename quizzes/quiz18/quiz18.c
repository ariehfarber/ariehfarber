/*******************************************************************************
*Auther: Arieh Farber
*******************************************************************************/
#include <stddef.h> /*size_t*/

#include "quiz18.h"

long *SumIntPairsToLongs(int ints[], size_t num_of_elements)
{
	size_t i = 0;
	long *runner = NULL;
	
	runner = (long *)ints;
	
	for (i = 0; i < num_of_elements; i += 2)
	{
		*runner = ((long)(ints[i] + (long)ints[i + 1]));
		runner++;
	}
	
	return ((long *)ints);
}


