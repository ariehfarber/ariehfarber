/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Artur Livshits
*Date: 18/11/2023
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <math.h>   /*pow   */
#include <string.h> /*strcmp*/

#include "ws6.h"

static void TestPow2();
static void TestIsPowOf2WithLoop();
static void TestIsPowOf2NoLoop();
static void TestAddOne();
static void TestThreeBitsOn();
static void TestByteMirrorWithLoop();
static void TestByteMirrorNoLoop();
static void TestIsBitsTwoAndSix();
static void TestIsBitsTwoOrSix();
static void TestSwapBitsThreeAndFive();
static void TestClosestDivisibleBy16();
static void TestSwapWithBits();
static void TestNumberOfBitsWithLoop();
static void TestNumberOfBitsNoLoop();
static void TestFloatInBits();

int main()
{
	TestPow2();
	TestIsPowOf2WithLoop();
	TestIsPowOf2NoLoop();
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

static void TestInt(int want, int got, int line);
static void TestUnsignedInt(unsigned int want, unsigned int got, int line);
static void TestUnsignedChar(unsigned char ctrl, unsigned char got, int line);
static void TestLong(long want, long got, int line);
static void PrintInBinary8Bits(char number);

static void TestPow2()
{
	unsigned int x = 4;
	unsigned int y = 3;
	
	TestLong((x * pow(2, y)), Pow2(x, y), __LINE__);
}

static void TestIsPowOf2WithLoop()
{
	unsigned int n = 5;
	unsigned int i = 0;
	unsigned int want[5] = {0, 1, 1, 0, 1};

	for (i = 0; i < n; ++i)
	{
		TestUnsignedInt(want[i], IsPowOf2WithLoop(i), __LINE__);
	}
}

static void TestIsPowOf2NoLoop()
{
	unsigned int n = 5;
	unsigned int i = 0;
	unsigned int want[5] = {0, 1, 1, 0, 1};

	for (i = 0; i < n; ++i)
	{
		TestUnsignedInt(want[i], IsPowOf2NoLoop(i), __LINE__);
	}
}

static void TestAddOne()
{
	int n = 50;

	TestInt(51, AddOne(n), __LINE__);
}

static void TestThreeBitsOn()
{
	unsigned int array[] = {1, 4 ,7, 9, 11, 15};
	unsigned int size = 0;
	
	size = sizeof(array)/sizeof(array[0]);
	
	ThreeBitsOn(array, size);
}

static void TestByteMirrorWithLoop()
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

static void TestByteMirrorNoLoop()
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

static void TestIsBitsTwoAndSix()
{
	unsigned char num = 35;
	int want = 1;

	TestInt(want, IsBitsTwoAndSix(num), __LINE__);
}

static void TestIsBitsTwoOrSix()
{
	unsigned char num = 32;
	int want = 1;

	TestInt(want, IsBitsTwoOrSix(num), __LINE__);
}

static void TestSwapBitsThreeAndFive()
{	
	unsigned char num = 16;
	unsigned char want = 4;
	
	TestUnsignedChar(want, SwapBitsThreeAndFive(num), __LINE__);
}

static void TestClosestDivisibleBy16()
{
	unsigned int num = 40;
	unsigned int want = 32;

	TestUnsignedInt(want, ClosestDivisibleBy16(num), __LINE__);
}

static void TestSwapWithBits()
{
	int x = 5;
	int y = 123;
	int want_x = 123;
	int want_y = 5;
	
	SwapWithBits(&x, &y);
	TestInt(want_x, x, __LINE__);
	TestInt(want_y, y, __LINE__);
}

static void TestNumberOfBitsWithLoop()
{
	int num = 7;
	int want = 3;
	
	TestInt(want, NumberOfBitsWithLoop(num), __LINE__);
}

static void TestNumberOfBitsNoLoop()
{
	int num = 8;
	int want = 1;

	TestInt(want, NumberOfBitsNoLoop(num), __LINE__);
}

static void TestFloatInBits()
{
	float num = 1.1;
	
	FloatInBits(num);
}

static void TestInt(int want, int got, int line)
{
	if (want != got)
	{
		printf("\033[0;31m");
		printf("Error. failed at line %d\n", line);
		printf("\033[0m"); 
	}
	else
	{
		printf("\033[1;32m");
		printf("Success!\n");
		printf("\033[0m"); 
	}
}

static void TestUnsignedInt(unsigned int want, unsigned int got, int line)
{
	if (want != got)
	{
		printf("\033[0;31m");
		printf("Error. failed at line %d\n", line);
		printf("\033[0m"); 
	}
	else
	{
		printf("\033[1;32m");
		printf("Success!\n");
		printf("\033[0m"); 
	}
}

static void TestUnsignedChar(unsigned char ctrl, unsigned char got, int line)
{
	if (ctrl != got)
	{
		printf("\033[0;31m");
		printf("Error. failed at line %d\n", line);
		printf("\033[0m"); 
	}
	else
	{
		printf("\033[1;32m");
		printf("Success!\n");
		printf("\033[0m"); 
	}
}

static void TestLong(long want, long got, int line)
{
	if (want != got)
	{
		printf("\033[0;31m");
		printf("Error. failed at line %d\n", line);
		printf("\033[0m"); 
	}
	else
	{
		printf("\033[1;32m");
		printf("Success!\n");
		printf("\033[0m"); 
	}
}

static void PrintInBinary8Bits(char number) 
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
