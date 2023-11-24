/*******************************************************************************
*Auther: Arieh Farber
*Reviewr: Igal Maikis
*Date: 5/11/2023
*******************************************************************************/
#include <stdio.h>  /*printf	*/
#include <math.h>   /*pow, fabs */

#include "ws1.h"

static void TestPrintStr();
static void TestPowerBaseTen();
static void TestFlipDigits();
static void TestSwap();

int main()
{
	TestPrintStr();
	TestPowerBaseTen();
	TestFlipDigits();
	TestSwap();
	
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

static void TestPrintStr()
{
	char *s = "\x22\x48\x65\x6c\x6c\x6f\x20\x77\x6f\x72\x6c\x64\x21\x22\n";
		
	PrintStr(s);
}

static void TestPowerBaseTen()
{
	int cases[] = {-1, 0, 3};
	int control[] = {0.1, 1, 1000};
	int size = 0;
	int i = 0;
	double epsilon = 0.05;
	
	size = sizeof(cases) / sizeof(cases[0]);
	
	for (i = 0; i < size; i++)
	{
		if ((control[i] - PowerBaseTen(cases[i])) > epsilon)
		{
			printf("\033[0;31m");
			printf("error in PowerBaseTen function result\n");
			printf("\033[0m");
		}
	}
}	

static void TestFlipDigits()
{
	int cases[] = {568, -1324, 0};
	int control[] = {865, -4231, 0};
	int size = 0;
	int i = 0;
	
	size = sizeof(cases) / sizeof(cases[0]);
	
	for (i = 0; i < size; i++)
	{
		TstResInt(control[i], FlipDigits(cases[i]), __LINE__);
	}
}

static void TestSwap()
{
	int x = 11;
	int y = 2785;
	
	IntSwap(&x ,&y);
	TstResInt(2785, x, __LINE__);
	TstResInt(11, y, __LINE__);
}
