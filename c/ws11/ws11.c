/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <stddef.h> /*size_t*/
#include <string.h> /*strlen*/
#include <assert.h> /*assert*/

#include "ws11.h"

#define ASCII_SIZE 256

static int CharToInt(char c)
{
	if ('0' <= c && '9' >= c) 
	{
		return ((int)c - '0');
	}
	else
	{
		return ((int)c - 'A' + 10); 
	}
}

static char IntToChar(int n)
{
	if (0 <= n && 9 >= n) 
	{
		return ((char)n + '0');
	}
	else
	{
		return ((char)n + 'A' - 10); 
	}
}

static char *StrRev(char *str)
{
	char *p1, *p2;

	assert(NULL != str);
		
	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; p1++, p2--)
	{
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}
	
	return (str);
}

int Atoi(const char *str)
{
	int digit = 0;
	int sign = 1;
	
	assert(NULL != str);
	
	while (' ' == *str || '\t' == *str)
	{
		str++;
	}
	
	if ('-' == *str)
	{
		sign = -1;
		str++;
	}
	
	while ('\0' != *str) 
	{
		if ('0' > *str || '9' < *str) 
		{
			return (digit);
		}
		
		digit *= 10;
		digit += *str - '0';
		str++;
	}
	
	return (digit * sign);
}

int AtoiAnyBase(const char *str, int base)
{
	int digit = 0;
	int sign = 1;
	
	assert(NULL != str);
	
	while (' ' == *str || '\t' == *str)
	{
		str++;
	}
	
	if ('-' == *str)
	{
		sign = -1;
		str++;
	}
	
	while ('\0' != *str) 
	{
		if (('0' > *str || '9' < *str) && ('A' > *str || 'Z' < *str)) 
		{
			return (digit);
		}
		
		if (CharToInt(*str) >= base)
		{
			return (digit);
		}

		digit *= base;
		digit += CharToInt(*str);
		str++;
	}
	
	return (digit * sign);
}

char* Itoa(int num, char* buffer)
{
	char *buffer_start = NULL;
	int digit = 0;
	int is_negative = 0;
	
	assert(NULL != buffer);
	
	buffer_start = buffer;

	if (0 == num)
	{
		*buffer = '0';
		buffer++;
		*buffer = '\0';
		return (buffer_start);
	}
	
	if (0 > num)
	{
		is_negative = 1;
		num = -num;
	}

	while (0 < num)
	{
		digit = num % 10;
		num /= 10;
		*buffer = digit + '0';
		buffer++;
	}
	
	if (1 == is_negative)
	{
		*buffer = '-';
		buffer++;
	}
	
	*buffer = '\0';
	
	StrRev(buffer_start);
	
	return (buffer_start);
}

char* ItoaAnyBase(int num, char* buffer, int base)
{
	char *buffer_start = NULL;
	int digit = 0;
	int is_negative = 0;
	
	assert(NULL != buffer);
	
	buffer_start = buffer;

	if (0 == num)
	{
		*buffer = '0';
		buffer++;
		*buffer = '\0';
		return (buffer_start);
	}
	
	if (0 > num)
	{
		is_negative = 1;
		num = -num;
	}

	while (0 < num)
	{
		digit = num % base;
		*buffer = IntToChar(digit);
		num /= base;
		buffer++;
	}
	
	if (1 == is_negative)
	{
		*buffer = '-';
		buffer++;
	}
	
	*buffer = '\0';
	
	StrRev(buffer_start);
	
	return (buffer_start);
}

void PrintArrOfChars(char *str1, char *str2 ,char *str3, size_t size1, 
					 size_t size2, size_t size3)
{
	size_t i = 0;
	char letter_table1[ASCII_SIZE] = {0};
	char letter_table2[ASCII_SIZE] = {0};
	
	for (i = 0; i < size1; i++)
	{
		if (('A' <= str1[i] && 'Z' >= str1[i]) || ('a' <= str1[i] && 'z' >= str1[i]))
		{
			letter_table1[CharToInt(str1[i])]++;
		}
	}
	
	for (i = 0; i < size2; i++)
	{
		if (('A' <= str1[i] && 'Z' >= str1[i]) || ('a' <= str1[i] && 'z' >= str1[i]))
		{
			letter_table1[CharToInt(str2[i])]++;
		}
	}
	
	for (i = 0; i < size3; i++)
	{
		if (('A' <= str1[i] && 'Z' >= str1[i]) || ('a' <= str1[i] && 'z' >= str1[i]))
		{
			letter_table1[CharToInt(str3[i])]++;
			letter_table2[CharToInt(str3[i])]++;
		}
	}
	
	for (i = 0; i < ASCII_SIZE; i++)
	{
		if (2 == letter_table1[i] && 0 == letter_table2[i])
		{
			printf("%c\n", IntToChar(letter_table1[i]));
		}
	}
}
















