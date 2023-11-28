/*******************************************************************************
*Auther: Arieh Farber
*******************************************************************************/
#include <stdio.h>  /*printf*/

#include "quiz8.h"

static void TestCountCoupledSetBits();
static void TestSwapWithBits();
static void TestSwapWithTemp();
static void TestSwapWithSum();
static void TestBitCounter();

int main()
{
	TestCountCoupledSetBits();
	TestSwapWithBits();
	TestSwapWithTemp();
	TestSwapWithSum();
	TestBitCounter();
	
	return (0);
}

static void TstResInt(int control, int func_res, int line)
{
	if (control != func_res)
	{
		printf("\033[0;31m");
		printf("Error. failed at line %d\n", line);
		printf("\033[0m"); 
	}
}

static void TestCountCoupledSetBits()
{
	char num = 7;
	int control = 2;
	
	TstResInt(control, CountCoupledSetBits(num), __LINE__);
}

static void TestSwapWithBits()
{
	int x = 7;
	int y = 0;
	int control_x = 0;
	int control_y = 7;
	
	SwapWithBits(&x, &y);
	TstResInt(control_x, x, __LINE__);
	TstResInt(control_y, y, __LINE__);
}

static void TestSwapWithTemp()
{
	int x = 85;
	int y = 12;
	int control_x = 12;
	int control_y = 85;
	
	SwapWithTemp(&x, &y);
	TstResInt(control_x, x, __LINE__);
	TstResInt(control_y, y, __LINE__);
}

static void TestSwapWithSum()
{
	int x = 10;
	int y = 20;
	int control_x = 20;
	int control_y = 10;
	
	SwapWithSum(&x, &y);
	TstResInt(control_x, x, __LINE__);
	TstResInt(control_y, y, __LINE__);
}

static void TestBitCounter()
{
	int num = 7;
	int control = 3;
	
	TstResInt(control, BitCounter(num), __LINE__);
}
