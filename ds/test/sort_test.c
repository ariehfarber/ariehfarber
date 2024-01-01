/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Elinor Fuchs
*Date: 01/01/2024
*******************************************************************************/
#include <stdio.h>  /*printf							   */
#include <stdlib.h> /*srand, rand, qsort				   */
#include <time.h>   /*time,, clock, clock_t, CLOCKS_PER_SEC*/

#include "sort.h"

#define TRUE  1
#define FALSE 0
#define ERROR -1
#define SUCCESS 0

static void TestSort();

int main()
{
	TestSort();

	return (0);
}

static void TestBubbleSort();
static void TestSelectionSort();
static void TestInsertionSort();
static void TestCountingSort();
static void TestRadixSort();

static int *RandomArrayGenerator(void);
static int *RandomArrayGenerator7Digits(void);
int CompareFunctionInt(const void *a, const void *b);
int IsArraySorted(int arr[], int size);
void TestInt(int want, int got, int line);

static void TestSort()
{
	TestBubbleSort();
	
	TestSelectionSort();
	
	TestInsertionSort();
	
	TestCountingSort();
	
	TestRadixSort();
}

static void TestBubbleSort()
{
	int *my_array = RandomArrayGenerator();
	int state = -1;
	clock_t start = 0;
	clock_t end = 0;
	double time = 0;
	
	start = clock();
	BubbleSort(my_array, 5000);
	end = clock();
	
	time = ((double)(end - start) / CLOCKS_PER_SEC);
	printf("Bubble sort time: %f [SEC]\n", time);
	state = IsArraySorted(my_array, 5000);
	TestInt(TRUE, state, __LINE__);
	
	my_array = RandomArrayGenerator();	
	start = clock();
	qsort(my_array, 5000, sizeof(int), CompareFunctionInt);
	end = clock();

	time = ((double)(end - start) / CLOCKS_PER_SEC);
	printf("Qsort time: %f [SEC]\n", time);	
	state = IsArraySorted(my_array, 5000);
	TestInt(TRUE, state, __LINE__);
	printf("\n");
}

static void TestSelectionSort()
{
	int *my_array = RandomArrayGenerator();
	int state = -1;
	clock_t start = 0;
	clock_t end = 0;
	double time = 0;
	
	start = clock();
	SelectionSort(my_array, 5000);
	end = clock();

	time = ((double)(end - start) / CLOCKS_PER_SEC);
	printf("Selection sort time: %f [SEC]\n", time);		
	state = IsArraySorted(my_array, 5000);	
	TestInt(TRUE, state, __LINE__);
	
	my_array = RandomArrayGenerator();	
	start = clock();
	qsort(my_array, 5000, sizeof(int), CompareFunctionInt);
	end = clock();
	
	time = ((double)(end - start) / CLOCKS_PER_SEC);
	printf("Qsort time: %f [SEC]\n", time);
	state = IsArraySorted(my_array, 5000);
	TestInt(TRUE, state, __LINE__);
	printf("\n");
}

static void TestInsertionSort()
{
	int *my_array = RandomArrayGenerator();
	int state = -1;
	clock_t start = 0;
	clock_t end = 0;
	double time = 0;
	
	start = clock();
	InsertionSort(my_array, 5000);
	end = clock();

	time = ((double)(end - start) / CLOCKS_PER_SEC);
	printf("Insertion sort time: %f [SEC]\n", time);
	state = IsArraySorted(my_array, 5000);
	TestInt(TRUE, state, __LINE__);
	
	my_array = RandomArrayGenerator();
	start = clock();
	qsort(my_array, 5000, sizeof(int), CompareFunctionInt);
	end = clock();

	time = ((double)(end - start) / CLOCKS_PER_SEC);
	printf("Qsort time: %f [SEC]\n", time);
	state = IsArraySorted(my_array, 5000);
	TestInt(TRUE, state, __LINE__);
	printf("\n");
}

static void TestCountingSort()
{
	int *my_array = RandomArrayGenerator();
	int state = -1;
	int counting_state = 0;
	clock_t start = 0;
	clock_t end = 0;
	double time = 0;
	
	start = clock();
	counting_state = CountingSort(my_array, 5000);
	TestInt(SUCCESS, counting_state, __LINE__);
	end = clock();

	time = ((double)(end - start) / CLOCKS_PER_SEC);
	printf("Counting sort time: %f [SEC]\n", time);
	state = IsArraySorted(my_array, 5000);
	TestInt(TRUE, state, __LINE__);
	
	my_array = RandomArrayGenerator();
	start = clock();
	qsort(my_array, 5000, sizeof(int), CompareFunctionInt);
	end = clock();

	time = ((double)(end - start) / CLOCKS_PER_SEC);
	printf("Qsort time: %f [SEC]\n", time);
	state = IsArraySorted(my_array, 5000);
	TestInt(TRUE, state, __LINE__);
	printf("\n");
}

static void TestRadixSort()
{
	int *my_array = RandomArrayGenerator7Digits();
	int state = -1;
	int radix_state = 0;
	clock_t start = 0;
	clock_t end = 0;
	double time = 0;
	
	start = clock();
	radix_state = RadixSort(my_array, 5000);
	TestInt(SUCCESS, radix_state, __LINE__);
	end = clock();

	time = ((double)(end - start) / CLOCKS_PER_SEC);
	printf("Radix sort time: %f [SEC]\n", time);
	state = IsArraySorted(my_array, 5000);
	TestInt(TRUE, state, __LINE__);
	
	my_array = RandomArrayGenerator7Digits();
	start = clock();
	qsort(my_array, 5000, sizeof(int), CompareFunctionInt);
	end = clock();

	time = ((double)(end - start) / CLOCKS_PER_SEC);
	printf("Qsort time: %f [SEC]\n", time);
	state = IsArraySorted(my_array, 5000);
	TestInt(TRUE, state, __LINE__);
	printf("\n");
}

static int *RandomArrayGenerator(void)
{
	static int random_array[5000];
	int i = 0;
	
    srand(time(NULL));
 
    for(i = 0; i < 5000; ++i)
    {
        random_array[i] = rand()%100 + 1;
    }
    
    return (random_array);
}

static int *RandomArrayGenerator7Digits(void)
{
	static int random_array[5000];
	int i = 0;
	
    srand(time(NULL));
 
    for(i = 0; i < 5000; ++i)
    {
        random_array[i] = rand()%999999 + 1000000;
    }
    
    return (random_array);
}

int CompareFunctionInt(const void *a, const void *b) 
{
   return (*(int*)a - *(int*)b);
}

int IsArraySorted(int arr[], int size)
{
    if (size == 1 || size == 0)
    {
	    return (TRUE);    
    }
    
    if (arr[size - 1] < arr[size - 2])
    {
        return (FALSE);
    }

    return (IsArraySorted(arr, size - 1));
}

void TestInt(int want, int got, int line)
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
