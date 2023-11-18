/***********************************************************************************
*Author: Arieh Farber 
*Reviewer: Artur Livshits
*Date: 18/11/2023
***********************************************************************************/
#include <stdio.h> /*printf*/
#include "ws6.h"

void TestPow2();
void TestIsPow2WithLoop();
void TestIsPow2NoLoop();
void TestAddOne();
void TestThreeBitsOn();
void TestByteMirrorWithLoop();
void TestByteMirrorNoLoop();
void TestIsBitsTwoAndSix();
void TestIsBitsTwoOrSix();
void TestSwapBitsThreeAndFive();
void TestClosestDivisibleBy16();
void TestSwapWithBits();
void TestNumberOfBitsWithLoop();
void TestNumberOfBitsNoLoop();
void TestFloatInBits();

int main()
{
	TestPow2();
	TestIsPow2WithLoop();
	TestIsPow2NoLoop();
	TestAddOne();
	TestThreeBitsOn();
	TestByteMirrorWithLoop();
	TestByteMirrorNoLoop();
	TestIsBitsTwoAndSix();
	TestIsBitsTwoOrSix();
	TestSwapBitsThreeAndFive();
	TestClosestDivisibleBy16();
	TestSwapWithBits();
	TestNumberOfBitsWithLoop();
	TestNumberOfBitsNoLoop();
	TestFloatInBits();
	
	return (0);
}

/***********************************************************************************
*Help function for printing numbers in binary
***********************************************************************************/
void PrintInBinary8Bits(char number) 
{
	int i = 0;
	char size = 0;
	char binaryDigit = 0;
	
	size = sizeof(unsigned char) * 8 - 1;
	
	printf("In binary ");
	for (i = size; i >= 0; i--) 
	{
		binaryDigit = (number >> i) & 1;
		printf("%d", binaryDigit);
	}
	printf("\n");
}

void PrintInBinary32Bits(unsigned int number) 
{
	int i = 0;
	int size = 0;
	int binaryDigit = 0;
	
	size = sizeof(unsigned int) * 8 - 1;
	
	printf("In binary ");
	for (i = size; i >= 0; i--) 
	{
		binaryDigit = (number >> i) & 1;
		printf("%d", binaryDigit);
	}
	printf("\n");
}

/***********************************************************************************
*Test exercise 1 
***********************************************************************************/
void TestPow2()
{
	unsigned int x = 4;
	unsigned int y = 3;
	long result = 0;
	
	result = Pow2(x, y);
	
	printf("Test Pow2:\n");
	printf("The resultult of %d*(2^%d) is %ld\n", x, y, result);
	printf("\n");
}

/***********************************************************************************
*Test exercise 2
***********************************************************************************/
void TestIsPow2WithLoop()
{
	unsigned int n = 4;
	unsigned int result = 0;
	unsigned i = 0;

	printf("Test IsPow2WithLoop:\n");
	for(i = 0; i <= n; i++)
	{
		result = IsPow2WithLoop(i);
		if(result == 1)
		{
			printf("%d is a power of 2\n", i);
		}
		else if(result == 0)
		{
			printf("%d is not a power of 2\n", i);
		}	
	}
	printf("\n");
}

void TestIsPow2NoLoop()
{
	unsigned int n = 4;
	unsigned int result = 0;
	unsigned int i = 0;

	printf("Test IsPow2NoLoop:\n");
	for(i = 0; i <= n; i++)
	{
		result = IsPow2NoLoop(i);
		if(result == 1)
		{
			printf("%d is a power of 2\n", i);
		}
		else if(result == 0)
		{
			printf("%d is not a power of 2\n", i);
		}	
	}
	printf("\n");
}

/***********************************************************************************
*Test exercise 3
***********************************************************************************/
void TestAddOne()
{
	int n = -1;
	int sum = 0;
	
	sum = AddOne(n);
	printf("Test AddOne:\n");
	printf("%d + 1 is %d\n\n", n, sum);
}

/***********************************************************************************
*Test exercise 4
***********************************************************************************/
void TestThreeBitsOn()
{
	unsigned int array[] = {1, 4 ,7, 9, 11, 15};
	unsigned int size = 0;
	
	size = sizeof(array)/sizeof(array[0]);
	
	ThreeBitsOn(array, size);
}

/***********************************************************************************
*Test exercise 5
***********************************************************************************/
void TestByteMirrorWithLoop()
{
	char num = 11;
	char mirror_num = 0;
	
	printf("Test ByteMirrorWithLoop:\n");
	printf("Original binary number ");
	PrintInBinary8Bits(num); 
	
	mirror_num = ByteMirrorWithLoop(num);

	printf("Mirrored Binary number ");
	PrintInBinary8Bits(mirror_num);
	printf("\n"); 
}

void TestByteMirrorNoLoop()
{
	char num = 7;
	char mirror_num = 0;
	
	printf("Test ByteMirrorNoLoop:\n");
	printf("Original binary number ");
	PrintInBinary8Bits(num); 
	
	mirror_num = ByteMirrorNoLoop(num);

	printf("Mirrored Binary number ");
	PrintInBinary8Bits(mirror_num); 
	printf("\n");
}

/***********************************************************************************
*Test exercise 6
***********************************************************************************/
void TestIsBitsTwoAndSix()
{
	unsigned char num = 35;
	char result = 0;
	
	printf("Test ISBitsTwoAndSix:\n");
	printf("Given number %d\n", num);
	PrintInBinary8Bits(num); 

	result = IsBitsTwoAndSix(num);
		if(result == 1)
		{
			printf("the 2nd and 6th bits are set\n");
		}
		else if(result == 0)
		{
			printf("the 2nd and 6th bits are not set\n");
		}	
	printf("\n");
}

void TestIsBitsTwoOrSix()
{
	unsigned char num = 32;
	char result = 0;
	
	printf("Test IsBitsTwoOrSix:\n");
	printf("Given number %d\n", num);
	PrintInBinary8Bits(num); 

	result = IsBitsTwoOrSix(num);
		if(result == 1)
		{
			printf("the 2nd or/and 6th bits are set\n");
		}
		else if(result == 0)
		{
			printf("the 2nd and 6th bits are not set\n");
		}	
	printf("\n");
}

void TestSwapBitsThreeAndFive()
{	
	unsigned char num = 16;
	unsigned char result = 0;
	
	printf("Test SwapBitsThreeAndFive:\n");
	printf("Given number %d\n", num);
	PrintInBinary8Bits(num); 

	result = SwapBitsThreeAndFive(num);
	printf("the 3rd or 5th bits swaped gives us %d\n", result);
	PrintInBinary8Bits(result); 
	printf("\n");
}

/***********************************************************************************
*Test exercise 7
***********************************************************************************/
void TestClosestDivisibleBy16()
{
	unsigned int num = 444150687;
	unsigned int result = 0;
	
	printf("Test ClosestDivisibleBy16:\n");
	printf("Given number %d\n", num);

	result = ClosestDivisibleBy16(num);
	printf("The closest number divisible by 16 with no remainder is %u\n", result);
	PrintInBinary32Bits(result);
	printf("\n"); 
}

/***********************************************************************************
*Test exercise 8
***********************************************************************************/
void TestSwapWithBits()
{
	int x = 5;
	int y = 123;
	
	printf("Test SwapWithBits:\n");
	printf("Before swap x = %u\n", x);
	printf("Before swap y = %u\n", y);
	
	SwapWithBits(&x, &y);
	
	printf("After swap x = %u\n", x);
	printf("After swap y = %u\n\n", y);	
}

/***********************************************************************************
*Test exercise 9
***********************************************************************************/
void TestNumberOfBitsWithLoop()
{
	int num = 7;
	int result = 0;
	
	result = NumberOfBitsWithLoop(num);
	
	printf("Test NumberOfBitsWithLoop:\n");
	printf("The number of bits in %d is %d\n\n", num, result);
}

void TestNumberOfBitsNoLoop()
{
	int num = 1156798;
	int result = 0;
	
	result = NumberOfBitsNoLoop(num);
	
	printf("Test NumberOfBitsNoLoop:\n");
	printf("The number of bits in %d is %d\n", num, result);
	PrintInBinary32Bits(num);
	printf("\n"); 
}

/***********************************************************************************
*Test exercise 10
***********************************************************************************/
void TestFloatInBits()
{
	float num = 1.1;
	
	FloatInBits(num);
}

