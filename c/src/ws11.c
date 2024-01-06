/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Yarden Shai
*Date: 28/11/2023
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <stddef.h> /*size_t*/
#include <string.h> /*strlen*/
#include <assert.h> /*assert*/

#include "ws11.h"

#define ASCII_LETTER_DIFF 10
#define NEGATIVE -1
#define POSITIVE 1
#define TRUE 1
#define FALSE 0
#define DECIMAL_BASE 10
#define ASCII_SIZE 256
#define TRUE_TRUE 2

static int CharToInt(char c);
static char IntToChar(int n);
static char *StrRev(char *str);

int Atoi(const char *str)
{
	return (AtoiAnyBase(str, DECIMAL_BASE));
}

int AtoiAnyBase(const char *str, int base)
{
	int digit = 0;
	int sign = POSITIVE;
	
	assert(NULL != str);
	
	while (' ' == *str || '\t' == *str)
	{
		++str;
	}
	
	if ('-' == *str)
	{
		sign = NEGATIVE;
		++str;
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
		++str;
	}
	
	return (digit * sign);
}

char* Itoa(int num, char* buffer)
{
	return (ItoaAnyBase(num, buffer, DECIMAL_BASE));
}

char* ItoaAnyBase(int num, char* buffer, int base)
{
	char *buffer_start = NULL;
	int digit = 0;
	int is_negative = FALSE;
	
	assert(NULL != buffer);
	
	buffer_start = buffer;

	if (0 == num)
	{
		*buffer = '0';
		++buffer;
		*buffer = '\0';
		return (buffer_start);
	}
	
	if (0 > num)
	{
		is_negative = TRUE;
		num = -num;
	}

	while (0 < num)
	{
		digit = num % base;
		*buffer = IntToChar(digit);
		num /= base;
		++buffer;
	}
	
	if (TRUE == is_negative)
	{
		*buffer = '-';
		++buffer;
	}
	
	*buffer = '\0';
	
	StrRev(buffer_start);
	
	return (buffer_start);
}

void PrintArrayOfChars(char *str1, char *str2 ,char *str3, size_t size1, 
					   size_t size2, size_t size3)
{
	size_t i = 0;
	char character_table[ASCII_SIZE] = {0};
	
    for (i = 0; i < size1; ++i) 
    {
        character_table[(int)str1[i]] = TRUE;
    }

    for (i = 0; i < size2; ++i) 
    {
        if (character_table[(int)str2[i]] == TRUE) 
        {
            character_table[(int)str2[i]] = TRUE_TRUE;
        }
    }

    for (i = 0; i < size3; ++i) 
    {
        character_table[(int)str3[i]] = FALSE;
    }

    for (i = 0; i < ASCII_SIZE; ++i) 
    {
        if (character_table[i] == TRUE_TRUE) 
        {
            printf("%c\n", (char)i);
        }
    }
}

int IsLittleEndian(void)
{
	int test = 1;
	int endian_res = FALSE;

	if (*(char *)&test == 1)
	{
		endian_res = TRUE;
	}

	return (endian_res);
}

static int CharToInt(char c)
{
	if ('0' <= c && '9' >= c) 
	{
		return ((int)c - '0');
	}
	else
	{
		return ((int)c - 'A' + ASCII_LETTER_DIFF); 
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
		return ((char)n + 'A' - ASCII_LETTER_DIFF); 
	}
}

static char *StrRev(char *str)
{
	char *p1, *p2;

	assert(NULL != str);
		
	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
	{
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}
	
	return (str);
}
