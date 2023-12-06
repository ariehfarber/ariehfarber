/*******************************************************************************
*Auther: Arieh Farber
*******************************************************************************/
#include <stdio.h>  /*printf*/

#include "quiz14.h"

static void TestCharacterCounter();
static void TestBitCounter();

int main()
{
	TestCharacterCounter();
	TestBitCounter();
	
	return (0);
}

static void TestCharacterCounter()
{
	char array[9] = {'a', 'a', 'a', '0', 'f', 'f', 'f', 'f', '0'};
	int i = 0;
	
	for (i = 0; i < 9; i++)
	{
		CharacterCounter(array[i]);
	}
}

static void TestBitCounter()
{
	long number = 7;
	size_t count = 0;
	
	count = BitCounter(number);
	
	printf("count %lu\n", count);
}
 

