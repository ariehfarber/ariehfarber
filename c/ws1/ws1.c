/*******************************************************************************
*Auther: Arieh Farber
*Reviewr: Igal Maikis
*Date: 5/11/2023
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <assert.h> /*assert*/

#include "ws1.h"

char *HexadecimalHelloWorld(void)
{
	static char str[] = \
	"\x22\x48\x65\x6c\x6c\x6f\x20\x77\x6f\x72\x6c\x64\x21\x22\x00";
	
	return (str);
}

double PowerBaseTen(signed int exponent)
{
	double sum = 1;
	double base = 10;
	int i = 0;
	
	if (0 > exponent)
	{
		for (i = 0; i < -exponent; i++)
		{
			sum /= base;	
		}	
	}

	for (i = 0; i < exponent; i++)
	{
		sum *= base;
	}
	
	return (sum);
}

int FlipDigits(signed int number)
{
	int fliped = 0;
	int sign = 1;
	int base = 10;
	
	if (0 > number) 
	{
		number = -number;
		sign = -1;
	}

	while (0 != number)
	{
		fliped = (fliped * base) + (number % base);
		number = number / base;
	}
	
	return (sign * fliped);
}

void Swap(signed int *var1, signed int *var2)
{
	int temp = 0;
	
	assert(NULL != var1);
	assert(NULL != var2);
	
	temp = *var1;
	*var1 = *var2;
	*var2 = temp;
}
