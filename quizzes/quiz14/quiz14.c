/*******************************************************************************
*Auther: Arieh Farber
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <stddef.h> /*size_t*/

#include "quiz14.h"

#define ASCII_SIZE 256

static size_t char_table[ASCII_SIZE];

void CharacterCounter(char c)
{
	size_t i = 0;
	size_t max = 0;
	size_t max_index = 0;
	
	char_table[(int)c]++;
	
	if ('0' == c)
	{
		for (i = 0; i < ASCII_SIZE; i++)
		{
			if (max < char_table[i])
			{
				max = char_table[i];
				max_index = i;
			}
		}
		printf("%c appeard %lu times\n", (char)max_index, char_table[max_index]);
		for (i = 0; i < ASCII_SIZE; i++)
		{
			char_table[i] = 0;
		}
	}
}

size_t BitCounter(long num)
{
	size_t counter = 0;
	
	while (0 != num)
	{
		num &= (num - 1);
		counter++;
	}
	
	return (counter);
}


