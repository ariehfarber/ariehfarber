/*******************************************************************************
*Auther: Arieh Farber
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <stdlib.h> /*free*/

#include "exam1.h"

static void TestFlipDigitsInNum();
static void TestFlipBit();
static void TestGetNFibonacciElement();
static void TestIntToString();
static void TestMultiplyBy8();
static void Testfoo();

int main()
{
	TestFlipDigitsInNum();
	TestFlipBit();
	TestGetNFibonacciElement();
	TestIntToString();
	TestMultiplyBy8();
	Testfoo();
	
	return (0);
}

static void TestFlipDigitsInNum()
{
	int number = -5460;
	
	number = FlipDigitsInNum(number);
	
	printf("Test FlipDigitsInNum\n");
	printf("%d\n", number);
}

static void TestFlipBit()
{
	int val = 7;
	int n = 2;
	
	val = FlipBit(val, n);
	printf("Test FlipBit\n");
	printf("%d\n", val);
}

static void TestGetNFibonacciElement()
{
	unsigned long number = 0;
	unsigned int n = 5;
	
	number = GetNFibonacciElement(n);
	printf("Test GetNFibonacciElement\n");
	printf("%lu\n", number);
}

static void TestIntToString()
{
	char *string;
	int n = 78954;
	
	string = IntToString(n);
	
	printf("Test IntToString\n");
	printf("%s\n", string);
	
	free(string);
}

static void TestMultiplyBy8()
{
	unsigned int number = 5;

	number = MultiplyBy8(number);
	printf("Test MultiplyBy8\n");
	printf("%d\n", number);
}

static void TestFoo()
{
	printf("Test Foo\n");
	Foo1();
	Foo2();
}









