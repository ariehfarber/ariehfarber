/***********************************************************************************
*Author: Arieh Farber 
*Reviewer: Artur Livshits
*Date: 
***********************************************************************************/
#include <stdio.h> /*printf*/
#include "ws6.h"

/***********************************************************************************
*Exercise 1
***********************************************************************************/
long Pow2(unsigned int x, unsigned int y)
{
	long result = 0;

	result = x << y;
	
	return result;	 
}

/***********************************************************************************
*Exercise 2
***********************************************************************************/
unsigned int IsPow2WithLoop(unsigned int n)
{
	if (n == 0)
	{
		return (0);		
	}

	while(0 == n % 2)
	{
		n = n >> 1;
	}

	return (n == 1);		
}

unsigned int IsPow2NoLoop(unsigned int n)
{
	if (n == 0)
	{
		return (0);		
	}

	return ((n & (n - 1)) == 0);		
}

/***********************************************************************************
*Exercise 3
***********************************************************************************/
int AddOne(int n)
{
	int mask = 1;

	/*Flip all the set bits until we find a 0*/
	while(n & mask)
	{
		n ^= mask;
		mask <<= 1;
	}
	
	/*Flip the rightmost 0 bit*/
	n ^= mask;
	
	return (n);
}

/***********************************************************************************
*Exercise 4
***********************************************************************************/
void ThreeBitsOn(unsigned int *arr, unsigned int size)
{
	unsigned int i = 0;
	unsigned int num = 0;
	unsigned int count = 0;
	unsigned int mask = 1;
	
	printf("ThreeBitsOn:\n");
	for(i = 0; i < size; i++)
	{
		num = arr[i];
		while(num)
		{
			count+= (num & mask);
			num >>= 1;
		}
		if(3 == count)
		{
		printf("%d has exactly 3 bits on\n", arr[i]);
		}
		count = 0;
	}
	printf("\n");
}

/***********************************************************************************
*Exercise 5
***********************************************************************************/
unsigned char ByteMirrorWithLoop(unsigned char n)
{
	int mirror_n = 0;
	int number_of_bits = sizeof(unsigned char) * 8;
	int i = 0;
	
	for(i = 0; i < number_of_bits; i++)
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

/***********************************************************************************
*Exercise 6
***********************************************************************************/
int IsBitsTwoAndSix(unsigned char n)
{
	int result = 0;
	
	result = n & 34;

	return(result == 34);
}

int IsBitsTwoOrSix(unsigned char n)
{
	int result_two = 0;
	int result_six = 0;
	
	result_two = n & 2;
	result_six = n & 32;

	return(result_two == 2 || result_six == 32);
}

unsigned char SwapBitsThreeAndFive(unsigned char n)
{
	unsigned char result_three = 0;
	unsigned char result_five = 0;
	unsigned char result = 0;
	
	result_three = n & 4;
	result_five = n & 16;
	
	result = result_three + result_five;
	
	if(result == 4 || result == 16)
	{
		n ^= 20;
	}

	return (n);
}

/***********************************************************************************
*Exercise 7
***********************************************************************************/
unsigned int ClosestDivisibleBy16(unsigned int n)
{
	n &= ~15;
		
	return (n);
}

/***********************************************************************************
*Exercise 8
***********************************************************************************/
void SwapWithBits(int *p1, int *p2)
{
	if(*p1 != *p2)
	{
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;	
	}	
}

/***********************************************************************************
*Exercise 9
***********************************************************************************/
int NumberOfBitsWithLoop(int n)
{
	int count = 0;

	while (n != 0) 
	{
		count += n & 1;
		n >>= 1;
	}
	
	return (count);
}

int NumberOfBitsNoLoop(int n)
{
	int count = 0;

	count = (n & 1) + ((n >> 1) & 1) + ((n >> 2) & 1) + ((n >> 3) & 1) + \
        ((n >> 4) & 1) + ((n >> 5) & 1) + ((n >> 6) & 1) + ((n >> 7) & 1) + \
        ((n >> 8) & 1) + ((n >> 9) & 1) + ((n >> 10) & 1) + ((n >> 11) & 1) + \
        ((n >> 12) & 1) + ((n >> 13) & 1) + ((n >> 14) & 1) + ((n >> 15) & 1) + \
        ((n >> 16) & 1) + ((n >> 17) & 1) + ((n >> 18) & 1) + ((n >> 19) & 1) + \
        ((n >> 20) & 1) + ((n >> 21) & 1) + ((n >> 22) & 1) + ((n >> 23) & 1) + \
        ((n >> 24) & 1) + ((n >> 25) & 1) + ((n >> 26) & 1) + ((n >> 27) & 1) + \
        ((n >> 28) & 1) + ((n >> 29) & 1) + ((n >> 30) & 1) + ((n >> 31) & 1);
	
	return (count);
}

/***********************************************************************************
*Exercise 10
***********************************************************************************/
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

	






































