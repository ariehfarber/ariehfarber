/***********************************************************************************
*Auther: Arieh Farber
*Reviewr: Yarden Shai
*Date: 8/11/2023
***********************************************************************************/

#include <assert.h> /*assert*/
#include <stddef.h> /*size_t*/
#include <string.h> /*strcmp*/
#include <stdlib.h> /*malloc*/
#include "wc2.h"

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

	for (i = 0; i < arry_size; i++)
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
	char *reverse_str = NULL;
	int length = 0;
	int value = 0;
	int i = 0;
		
	length = strlen(str);
	
	reverse_str = (char *)malloc(length +1);
	
	for (i = 0; i < length; ++i) 
	{
		reverse_str[length - i - 1] = str[i];
	}
	reverse_str[length] = '\0';
	
	value = strcmp(str, reverse_str);
	
	free(reverse_str);
	
	return(value);
}

















