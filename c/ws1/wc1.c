/* wc1.c */

#include <stdio.h> /* added for the printf() function */
#include <string.h> /* added for the strlen() function */
#include <math.h> /* added for the pow() and fabs() function */
#include <assert.h> /* added for the assert() function */

/* Exercise 3: "Hello World!" */
void HelloWorld()
{
	char str[] ={0x22, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x77, 
	0x6f, 0x72, 0x6c, 0x64, 0x21, 0x22, 0x00};
	int size = strlen(str);
	int i;
	
	for (i = 0; i < size; i++)
	{
		printf("%c", str[i]);
	}
	printf("\n");
}

/* Exercise 4: 10 to the Power of n */
double PowerOfTen(int n)
{
	double sum=1.0;
	int i;
	
	if (n < 0)
	{
		for (i = 0; i < -n; i++)
		{
			sum /= 10.0;	
		}	
	}
	else
	{
		for (i = 0; i < n; i++)
		{
			sum *= 10.0;
		}
	}
	
	return sum;
}

/* Exercise 5: flipping digits */
int FlipDigits(int n)
{
	int fliped = 0;
	int marker = 1;
	
	if (n < 0)
	{
		n = -n;
		marker = -1;
	}

	while (n != 0)
	{
	fliped = (fliped * 10) + (n % 10);
	n = n / 10;
	}
	
	return fliped * marker;
}

/* Exercise 6: swap variables */
void Swap(int *var1, int *var2)
{
	int temp;
	
	assert(var1 != NULL && var2 != NULL);
	
	temp = *var1;
	*var1 = *var2;
	*var2 = temp;
}

/* Test exercises */

/* Test exercise 4 */
void TestPowerOfTen()
{
	int test_case[] = {-1, 0, 3};
	int size = sizeof(test_case) / sizeof(test_case[0]);
	int i;
	double result;
	
	for (i = 0; i < size; i++)
	{
		result = PowerOfTen(test_case[i]);
		printf("ten to the power of %d is %f\n", test_case[i], result);
		
		if (fabs(pow(10, test_case[i]) - result) > 0.05)
		{
			printf("error in PowerOfTen function result\n");
		}
	}
}

/* Test exercise 5 */
void TestFlipDigits()
{
	int test_case[] = {568, 1324, 0 , -45682, -300, 3};
	int size = sizeof(test_case) / sizeof(test_case[0]);
	int i;
	int result;
	
	for (i = 0; i < size; i++)
	{
		result = FlipDigits(test_case[i]);
		printf("original: %d, flippd: %d\n", test_case[i], result);
	}
}

/* Test exercise 6 */
void TestSwap()
{
	int x = 7;
	int y = 3;
	
	printf("original: x=%d, y=%d\n", x, y);
	Swap(&x ,&y);
	printf("swapped: x=%d, y=%d\n", x, y);
}

/* main */
int main()
{
	HelloWorld();
	TestPowerOfTen();
	TestFlipDigits();
	TestSwap();
	return 0;
}























