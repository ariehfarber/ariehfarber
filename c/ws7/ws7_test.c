/***********************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
***********************************************************************************/
#include <stdio.h>  /*printf*/

#include "ws7.h"

#define MAX2(a, b) ((a > b) ? a : b)

#define MAX3(a, b, c) ( (a > b && a > c) ? a : ( b > c) ? b : c )  

#define SIZEOF_VAR(a) ((size_t)(&a + 1)-(size_t)(&a)) 

#define SIZEOF_TYPE(type) ((size_t)((char *)(&((type *)0)[1]) - (char *)((type *)0)))

void TestListElements();
void TestMax2();
void TestMax3();
void TestSizeOfVar();
void TestSizeOfType();

int main()
{
	TestListElements();
	TestMax2();
	TestMax3();
	TestSizeOfVar();
	TestSizeOfType();
	
	return (0);
}

void TestListElements()
{
	ListElements();
}

void TestMax2()
{
	int max = 0;
	int a = 10, b = 45;
	
	max = MAX2(a,b);
	
	printf("Maximum number is: %d\n",max);
}

void TestMax3()
{
	int max = 0;
	int a = 10, b = 45, c = 101;
	
	max = MAX3(a, b, c);
	
	printf("Maximum number is: %d\n",max);
}

void TestSizeOfVar()
{
	int x = 0; 
	
	printf("sizeof x is: %lu\n",SIZEOF_VAR(x));
}

void TestSizeOfType()
{
	printf("sizeof x is: %lu\n",SIZEOF_TYPE(long));
}



