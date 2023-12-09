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

void TestInt(int control, int test, int line)
{
	if (control != test)
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

void TestDouble(double control, double test, int line)
{
	if (control < test)
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

void TestChar(char *control, char *test, int line)
{
	if (0 != strcmp(control, test))
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

static void TestHexadecimalHelloWorld()
{
	char *s = NULL;
	char *control = "\"Hello world!\"";
		
	s = HexadecimalHelloWorld();
	
	TestChar(control, s, __LINE__);
}

static void TestPowerBaseTen()
{
	int test_cases[] = {-1, 0, 3};
	int control[] = {0.1, 1, 1000};
	int size = 0;
	int i = 0;
	double epsilon = 0.05;
	double test_val = 0.0;
	
	size = sizeof(test_cases) / sizeof(test_cases[0]);
	
	for (i = 0; i < size; i++)
	{
		test_val = control[i] - PowerBaseTen(test_cases[i]);
		
		TestDouble(epsilon, test_val, __LINE__);
	}
}	

static void TestFlipDigits()
{
	int test_cases[] = {568, -1324, 0};
	int control[] = {865, -4231, 0};
	int size = 0;
	int i = 0;
	
	size = sizeof(test_cases) / sizeof(test_cases[0]);
	
	for (i = 0; i < size; i++)
	{
		TestInt(control[i], FlipDigits(test_cases[i]), __LINE__);
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
