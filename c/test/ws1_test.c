/*******************************************************************************
*Auther: Arieh Farber
*Reviewr: Igal Maikis
*Date: 5/11/2023
*******************************************************************************/
#include <stdio.h>  /*printf	*/
#include <math.h>   /*pow, fabs */
#include <string.h> /*strcmp	*/

#include "ws1.h"

static void TestHexadecimalHelloWorld();
static void TestPowerBaseTen();
static void TestFlipDigits();
static void TestSwap();

int main()
{
	TestHexadecimalHelloWorld();
	TestPowerBaseTen();
	TestFlipDigits();
	TestSwap();
	
	return (0);
}

static void TestInt(int want, int got, int line);
static void TestDouble(double want, double got, int line);
static void TestChar(char *want, char *got, int line);

static void TestHexadecimalHelloWorld()
{
	char *s = NULL;
	char *want = "\"Hello world!\"";
		
	s = HexadecimalHelloWorld();
	
	TestChar(want, s, __LINE__);
}

static void TestPowerBaseTen()
{
	int got_cases[] = {-1, 0, 3};
	int want[] = {0.1, 1, 1000};
	int size = 0;
	int i = 0;
	double epsilon = 0.05;
	double got_val = 0.0;
	
	size = sizeof(got_cases) / sizeof(got_cases[0]);
	
	for (i = 0; i < size; ++i)
	{
		got_val = want[i] - PowerBaseTen(got_cases[i]);
		
		TestDouble(epsilon, got_val, __LINE__);
	}
}	

static void TestFlipDigits()
{
	int got_cases[] = {568, -1324, 0};
	int want[] = {865, -4231, 0};
	int size = 0;
	int i = 0;
	
	size = sizeof(got_cases) / sizeof(got_cases[0]);
	
	for (i = 0; i < size; ++i)
	{
		TestInt(want[i], FlipDigits(got_cases[i]), __LINE__);
	}
}

static void TestSwap()
{
	int x = 11;
	int y = 2785;
	
	Swap(&x ,&y);
	TestInt(2785, x, __LINE__);
	TestInt(11, y, __LINE__);
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

static void TestDouble(double want, double got, int line)
{
	if (want < got)
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

static void TestChar(char *want, char *got, int line)
{
	if (0 != strcmp(want, got))
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
