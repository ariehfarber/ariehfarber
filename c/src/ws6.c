/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Artur Livshits
*Date: 18/11/2023
*******************************************************************************/
#include <stdio.h> /*printf*/

#include "ws6.h"

long Pow2(unsigned int x, unsigned int y)
{
	return (x << y);	 
}

unsigned int IsPowOf2WithLoop(unsigned int n)
{
	if (0 == n)
	{
		return (0);		
	}

	while (0 == (n & 1))
	{
		n >>= 1;
	}

	return (1 == n);		
}

unsigned int IsPowOf2NoLoop(unsigned int n)
{
	if (0 == n)
	{
		return (0);		
	}

	return (0 == (n & (n - 1)));		
}

int AddOne(int n)
{
	int mask = 1;

	while (1 == (n & mask))
	{
		n ^= mask;
		mask <<= 1;
	}
	
	return (n ^= mask);
}

void ThreeBitsOn(unsigned int *arr, unsigned int size)
{
	unsigned int i = 0;
	unsigned int num = 0;
	unsigned int count = 0;
	unsigned int mask = 1;
	
	printf("\nThreeBitsOn:\n");
	for (i = 0; i < size; ++i)
	{
		num = arr[i];
		
		while (num)
		{
			count+= (num & mask);
			num >>= 1;
		}
		
		if (3 == count)
		{
			printf("%d has exactly 3 bits on\n", arr[i]);
		}	
		count = 0;
	}
	printf("\n");
}

unsigned char ByteMirrorWithLoop(unsigned char n)
{
	int mirror_n = 0;
	int number_of_bits = sizeof(unsigned char) * 8;
	int i = 0;
	
	for (i = 0; i < number_of_bits; ++i)
	{
		mirror_n |= (((n >> i) & 1) << (number_of_bits - 1 - i));
	}
	
	return (mirror_n);
}

unsigned char ByteMirrorNoLoop(unsigned char n)
{
	n = (n & 240) >> 4 | (n & 15) << 4;  
	n = (n & 204) >> 2 | (n & 51) << 2;  
	n = (n & 170) >> 1 | (n & 85) << 1;  
	
	return (n);
}

int IsBitsTwoAndSix(unsigned char n)
{
	return (34 == (n & 34));
}

int IsBitsTwoOrSix(unsigned char n)
{
	return (2 == (n & 2) || 32 == (n & 32));
}

unsigned char SwapBitsThreeAndFive(unsigned char n)
{
	unsigned char result = 0;

	result = (n & 4) + (n & 16);
	
	if (4 == result || 16 == result)
	{
		n ^= 20;
	}

	return (n);
}

unsigned int ClosestDivisibleBy16(unsigned int n)
{	
	return (n &= ~15);
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

int NumberOfBitsWithLoop(int n)
{
	int count = 0;

	while (0 != n) 
	{
		count += n & 1;
		n >>= 1;
	}
	
	return (count);
}

int NumberOfBitsNoLoop(int n)
{
	int count = 0;

	count = (n & 1) + ((n >> 1) & 1) + ((n >> 2) & 1) + \
			((n >> 3) & 1) + ((n >> 4) & 1) + ((n >> 5) & 1) + \
			((n >> 6) & 1) + ((n >> 7) & 1) + ((n >> 8) & 1) + \
			((n >> 9) & 1) + ((n >> 10) & 1) + ((n >> 11) & 1) + \
      	    ((n >> 12) & 1) + ((n >> 13) & 1) + ((n >> 14) & 1) + \
      	    ((n >> 15) & 1) + ((n >> 16) & 1) + ((n >> 17) & 1) + \
      	    ((n >> 18) & 1) + ((n >> 19) & 1) + ((n >> 20) & 1) + \
      	    ((n >> 21) & 1) + ((n >> 22) & 1) + ((n >> 23) & 1) + \
      	    ((n >> 24) & 1) + ((n >> 25) & 1) + ((n >> 26) & 1) + \
      	    ((n >> 27) & 1) + ((n >> 28) & 1) + ((n >> 29) & 1) + \
      	    ((n >> 30) & 1) + ((n >> 31) & 1);
	
	return (count);
}

void FloatInBits(float f_num)
{
	float *f_ptr = NULL;
	unsigned int *i_ptr = NULL;
	int i = 0;
	int size = 0;
	int binaryDigit = 0;
	unsigned int number = 0;
	
	f_ptr = &f_num;	
	i_ptr = (unsigned int *) f_ptr;
	number = *i_ptr;
	size = sizeof(float) * 8 - 1;
	
	printf("FloatInBits:\n");
	printf("Given number %f in binary\n", f_num);
	for (i = size; i >= 0; i--) 
	{
		binaryDigit = (number >> i) & 1;
		printf("%d", binaryDigit);
	}
	printf("\n");
}

