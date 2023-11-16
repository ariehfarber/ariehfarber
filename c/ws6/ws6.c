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
int ByteMirrorWithLoop(int n)
{
	int mirror_n = 0;
	int number_of_bits = sizeof(int) * 8;
	int i = 0;
	
	for(i = 0; i < number_of_bits; i++)
	{
		mirror_n |= (((n >> i) & 1) << (number_of_bits - 1 - i));
	}
	
	return (mirror_n);
}

int ByteMirrorNoLoop(int n)
{

}




















