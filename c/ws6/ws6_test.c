/***********************************************************************************
*Author: Arieh Farber 
*Reviewer: Artur Livshits
*Date: 
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
*Help function for printing number in binary
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
	long res = 0;
	
	res = Pow2(x, y);
	
	printf("Test Pow2:\n");
	printf("The result of %d*(2^%d) is %ld\n", x, y, res);
	printf("\n");
}

/***********************************************************************************
*Test exercise 2
***********************************************************************************/
void TestIsPow2WithLoop()
{
	unsigned int n = 4;
	unsigned int res = 0;
	unsigned i = 0;

	printf("Test IsPow2WithLoop:\n");
	for(i = 0; i <= n; i++)
	{
		res = IsPow2WithLoop(i);
		if(res == 1)
		{
			printf("%d is a power of 2\n", i);
		}
		else if(res == 0)
		{
			printf("%d is not a power of 2\n", i);
		}	
	}
	printf("\n");
}

void TestIsPow2NoLoop()
{
	unsigned int n = 4;
	unsigned int res = 0;
	unsigned int i = 0;

	printf("Test IsPow2NoLoop:\n");
	for(i = 0; i <= n; i++)
	{
		res = IsPow2NoLoop(i);
		if(res == 1)
		{
			printf("%d is a power of 2\n", i);
		}
		else if(res == 0)
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
	int n = 165;
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

	printf(" Mirrored Binary number ");
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

	printf(" Mirrored Binary number ");
	PrintInBinary8Bits(mirror_num); 
	printf("\n");
}

/***********************************************************************************
*Test exercise 6
***********************************************************************************/
void TestIsBitsTwoAndSix()
{
	unsigned char num = 35;
	char res = 0;
	
	printf("Test ISBitsTwoAndSix:\n");
	printf("Given number %d\n", num);
	PrintInBinary8Bits(num); 

	res = IsBitsTwoAndSix(num);
		if(res == 1)
		{
			printf("the 2nd and 6th bits are set\n");
		}
		else if(res == 0)
		{
			printf("the 2nd and 6th bits are not set\n");
		}	
	printf("\n");
}

void TestIsBitsTwoOrSix()
{
	unsigned char num = 32;
	char res = 0;
	
	printf("Test IsBitsTwoOrSix:\n");
	printf("Given number %d\n", num);
	PrintInBinary8Bits(num); 

	res = IsBitsTwoOrSix(num);
		if(res == 1)
		{
			printf("the 2nd or/and 6th bits are set\n");
		}
		else if(res == 0)
		{
			printf("the 2nd and 6th bits are not set\n");
		}	
	printf("\n");
}

void TestSwapBitsThreeAndFive()
{	
	unsigned char num = 16;
	unsigned char res = 0;
	
	printf("Test SwapBitsThreeAndFive:\n");
	printf("Given number %d\n", num);
	PrintInBinary8Bits(num); 

	res = SwapBitsThreeAndFive(num);
	printf("the 3rd or 5th bits swaped gives us %d\n", res);
	PrintInBinary8Bits(res); 
	printf("\n");
}

/***********************************************************************************
*Test exercise 7
***********************************************************************************/
void TestClosestDivisibleBy16()
{
	unsigned int num = 444150687;
	unsigned int res = 0;
	
	printf("Test ClosestDivisibleBy16:\n");
	printf("Given number %d\n", num);

	res = ClosestDivisibleBy16(num);
	printf("The closest number divisible by 16 with no remainder is %u\n", res);
	PrintInBinary32Bits(res);
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
	int res = 0;
	
	res = NumberOfBitsWithLoop(num);
	
	printf("Test NumberOfBitsWithLoop:\n");
	printf("The number of bits in %d is %d\n\n", num, res);
}

void TestNumberOfBitsNoLoop()
{
	int num = 1156798;
	int res = 0;
	
	res = NumberOfBitsNoLoop(num);
	
	printf("Test NumberOfBitsNoLoop:\n");
	printf("The number of bits in %d is %d\n", num, res);
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




















