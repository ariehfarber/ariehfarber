/***********************************************************************************
*Auther: Arieh Farber
*Reviewr: Igal Maikis
*Date: 5/11/2023
***********************************************************************************/

#include <stdio.h>  /*printf()     */
#include <string.h> /*strlen()     */
#include <math.h>   /*pow(), fabs()*/
#include <assert.h> /*assert()     */

void HelloWorld();
void TestPowerBaseTen();
void TestFlipDigits();
void TestSwap();

int main()
{
	HelloWorld();
	TestPowerBaseTen();
	TestFlipDigits();
	TestSwap();
	
	return (0);
}

/*Print "Hello World!" using hex values*/
void HelloWorld()
{
	char *str = "\x22\x48\x65\x6c\x6c\x6f\x20\x77\x6f\x72\x6c\x64\x21\x22\n";

	printf("%s", str);
}

/*10 to the Power of n*/
double PowerBaseTen(signed int exponent)
{
	double sum = 1;
	double base = 10;
	int i = 0;
	
	
	if (0 > exponent)
	{
		for (i = 0; i < -exponent; i++)
		{
			sum /= base;	
		}	
	}

	for (i = 0; i < exponent; i++)
	{
		sum *= base;
	}
	
	
	return (sum);
}

/*Test PowerBaseTen*/
void TestPowerBaseTen()
{
	int test_cases[] = {-1, 0, 3};
	int size = sizeof(test_cases) / sizeof(test_cases[0]);
	int i = 0;
	double result = 0;
	double epsilon = 0.05;
	
	for (i = 0; i < size; i++)
	{
		result = PowerBaseTen(test_cases[i]);
		printf("ten to the power of %d is %f\n", test_cases[i], result);
		
		if (fabs(pow(10, test_cases[i]) - result) > epsilon)
		{
			printf("error in PowerBaseTen function result\n");
		}
	}
}

/*Flip a numbers digits*/
int FlipDigits(signed int number)
{
	int fliped = 0;
	int marker = 1;
	int base = 10;
	
	if (number < 0) 
	{
		number = -number;
		marker = -1;
	}

	while (0 != number)
	{
		fliped = (fliped * base) + (number % base);
		number = number / base;
	}
	
	return (fliped * marker);
}

/*Test FlipDigits*/
void TestFlipDigits()
{
	int test_cases[] = {568, 1324, 0 , -45682, -300, 3};
	int size = sizeof(test_cases) / sizeof(test_cases[0]);
	int i = 0;
	int result = 0;
	
	for (i = 0; i < size; i++)
	{
		result = FlipDigits(test_cases[i]);
		printf("original: %d, flippd: %d\n", test_cases[i], result);
	}
}

/*Swap two integer variables*/
void Swap(signed int *var1, signed int *var2)
{
	int temp = 0;
	
	assert(NULL != var1);
	assert(NULL != var2);
	
	temp = *var1;
	*var1 = *var2;
	*var2 = temp;
}

/*Test Swap*/
void TestSwap()
{
	int x = 7;
	int y = 3;
	
	printf("original: x=%d, y=%d\n", x, y);
	Swap(&x ,&y);
	printf("swapped: x=%d, y=%d\n", x, y);
}
























