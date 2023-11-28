/*******************************************************************************
*Auther: Arieh Farber
*******************************************************************************/
#include "quiz8.h"

int CountCoupledSetBits(char n)
{
	int count = 0;
	
	while (n)
	{
		if((n & 3) == 3)
		{
			count++;
		}
		n >>= 1;
	}
	
	return (count);
}

void SwapWithBits(int *p1, int *p2)
{
	if (*p1 != *p2)
	{
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;	
	}	
}

void SwapWithTemp(int *p1, int *p2)
{
	int temp = 0;
	
	temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

void SwapWithSum(int *p1, int *p2)
{
	*p1 = *p1 + *p2;
	*p2 = *p1 - *p2;
	*p1 = *p1 - *p2;
}

int BitCounter(int n)
{
	int count = 0;
	
	while (n)
	{
		n = n & (n - 1);
		count++;
	}
	
	return (count);
}



















