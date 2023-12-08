/*******************************************************************************
*Auther: Arieh Farber
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <stddef.h> /*size_t*/
#include <stdlib.h> /*malloc*/
#include <string.h> /*strlen*/

#include "exam1.h"

#define ERROR -1

int FlipDigitsInNum(int num)
{
	int sign = 1;
	int n = 0;
	
	if (0 < num)
	{
		sign = -1;
		num = -num;
	}
	
	while (0 != num)
	{
		n *= 10;
		n = n + num % 10;
		num = (num - num % 10) / 10;
	}
	
	return (sign * n);
}

int FlipBit(int val, unsigned int n)
{
	if (32 < n)
	{
		return (ERROR);
	}
	
	return (val ^ (1 << n));
}

unsigned long GetNFibonacciElement(unsigned int n)
{
	unsigned long  value = 0, prev = 0, current = 1;
	
	while (1 != n)
	{
		value = current + prev;
		prev = current;
		current = value;
		n--;
	}
	
	return (value);
}

char *IntToString(int n)
{
    char *str = NULL;
    int count = 0;
    int num = 0;
    
    num = n;

    while (0 != num)
    {
        num = num / 10;
        count++;
    }
    
    str = (char *)malloc(count + 1); 
    if (NULL == str) 
    {
       return NULL; 
    }
    
    sprintf(str, "%d", n);
    
    return (str);
}

unsigned int MultiplyBy8(unsigned int n)
{
	return (n << 3);
}

void Foo1()
{
    char *s1 = "hello";
    char s2[] = "hello";
    char *s3 = s1;
    
    printf("%lu %lu %lu %lu \n", sizeof(s1),sizeof(s2),strlen(s1),strlen(s2));
    
    s3[0] = 'H';
    printf("%s \n", s3);
}

void Foo2()
{
    size_t array [] = {0, 1, 2, 3, 4, 5};
    size_t val = 3;
    
    printf("%lu \n", val[array]);
}











