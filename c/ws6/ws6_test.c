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

int main()
{
	TestPow2();
	TestIsPow2WithLoop();
	TestIsPow2NoLoop();
	TestAddOne();
	TestThreeBitsOn();
	TestByteMirrorWithLoop();
	TestByteMirrorNoLoop();
	
	return (0);
}

/***********************************************************************************
*Help function
***********************************************************************************/
void PrintInBinary(int number) 
{
	int i = 0;
	int size = 0;
	int binaryDigit = 0;
	
	size = sizeof(int) * 8 - 1;
	
	for (i = size; i >= 0; i--) 
	{
		binaryDigit = (number >> i) & 1;
		printf("%d", binaryDigit);
	}
	printf("\n");
}

/***********************************************************************************
*Exercise 1
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
*Exercise 2
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
*Exercise 3
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
*Exercise 4
***********************************************************************************/
void TestThreeBitsOn()
{
	unsigned int array[] = {1, 4 ,7, 9, 11, 15};
	unsigned int size = 0;
	
	size = sizeof(array)/sizeof(array[0]);
	
	ThreeBitsOn(array, size);
}

/***********************************************************************************
*Exercise 5
***********************************************************************************/
void TestByteMirrorWithLoop()
{
	int num = 11;
	int mirror_num = 0;
	
	printf("Test ByteMirrorWithLoop:\n");
	printf("	Original number ");
	PrintInBinary(num); 
	
	mirror_num = ByteMirrorWithLoop(num);

	printf(" Mirrored Binary number ");
	PrintInBinary(mirror_num); 
}

void TestByteMirrorNoLoop()
{

}































