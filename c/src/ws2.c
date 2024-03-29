/*******************************************************************************
*Author: Arieh Farber
*Reviewer: Yarden Shai
*Date: 9/11/2023
*******************************************************************************/
#include <assert.h>  /*assert */
#include <stddef.h>  /*size_t */
#include <string.h>  /*strcmp */
#include <stdlib.h>  /*malloc */

#define TRUE 1
#define FALSE 0

#include "ws2.h"

void IntSwap(int *var1, int *var2)
{
	int temp = 0;
	
	assert(NULL != var1);
	assert(NULL != var2);
	
	temp = *var1;
	*var1 = *var2;
	*var2 = temp;
}

void CopyArray(int *arry, int *arry_copy, int arry_size)
{
	int i;

	for (i = 0; i < arry_size; ++i)
	{
		arry_copy[i] = arry[i];
	}
}

void TSizeSwap(size_t *var1, size_t *var2)
{
	size_t temp = 0;
	
	assert(var1 && var2);
	
	temp = *var1;
	*var1 = *var2;
	*var2 = temp;
}

void PtrSwap(size_t **ptr1, size_t **ptr2)
{
	size_t *temp = NULL;
	
	assert(ptr1 && ptr2);
	
	temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}


void PtrSwapCombo(size_t **ptr1, size_t **ptr2)
{
	TSizeSwap(*ptr1, *ptr2);
}

int IsPalindrome(const char *str)
{
	size_t length = 0;
	size_t i = 0 ,j = 0;
		
	length = strlen(str);
		
	for (i = 0, j = length - 1; i < length; ++i, --j) 
	{
		if (str[i] != str[j])
		{
			return(FALSE);	
		}
	}
		
	return(TRUE);
}
