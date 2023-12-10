/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Artur Livshits 
*Date: 29/11/2023
*******************************************************************************/
#include <stdio.h>  /*printf  */
#include <stdlib.h> /*malloc  */
#include <stddef.h> /*size_t  */
#include <stdint.h> /*SIZE_MAX*/
#include <limits.h> /*CHAR_BIT*/

#include "bitarray.h"

#define BYTE_SIZE CHAR_BIT

static void TestBitArrayGetVal();
static void TestBitArraySetBit();
static void TestBitArrayResetAll();
static void TestBitArraySetAll();
static void TestBitArrayFlip();
static void TestBitArrayCountOn();
static void TestBitArrayCountOff();
static void TestBitArrayToString();
static void TestBitArrayRotateLeft();
static void TestBitArrayRotateRight();
static void TestBitArrayMirror();
static void TestBitArrayCountOnLUT();
static void TestBitArrayMirrorLUT();

int main()
{
	TestBitArrayGetVal();
	TestBitArraySetBit();
	TestBitArrayResetAll();
	TestBitArraySetAll();
	TestBitArrayFlip();
	TestBitArrayCountOn();
	TestBitArrayCountOff();
	TestBitArrayToString();
	TestBitArrayRotateLeft();
	TestBitArrayRotateRight();
	TestBitArrayMirror();
	TestBitArrayCountOnLUT();
	TestBitArrayMirrorLUT();
	
	return (0);
}

static void TestInt(int control, int test, int line)
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

static void TestSizeT(size_t control, size_t test, int line)
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

static void TestBitArray(bitarray_t control, bitarray_t test, int line)
{
	if (control != test)
	{
		printf("\033[0;31m");
		printf("Error. Failed at line %d\n", line);
		printf("\033[0m"); 
	}
	else
	{
		printf("\033[1;32m");
		printf("Success!\n");
		printf("\033[0m"); 
	}
}

static void PrintInBinary64Bits(bitarray_t number) 
{
	int i = 0;
	char size = 0;
	char binaryDigit = 0;
	
	size = sizeof(size_t) * BYTE_SIZE - 1;
	
	printf("Control ");
	for (i = size; i >= 0; i--) 
	{
		binaryDigit = (number >> i) & 1;
		printf("%d", binaryDigit);
	}
	printf("\n");
}

static void TestBitArrayGetVal()
{
	bitarray_t test_bit_array = 16;
	size_t test_index = 5;
	int test_val = 0;
	int control_val = 1;
	
	test_val = BitArrayGetVal(test_bit_array, test_index);
	
	TestInt(control_val, test_val, __LINE__);
}

static void TestBitArraySetBit()
{
	bitarray_t test_bit_array = 7;
	size_t test_index = 4;
	int bool_val = 1;
	bitarray_t control_bit_array = 15;
	
	test_bit_array = BitArraySetBit(test_bit_array, test_index, bool_val);
	
	TestBitArray(control_bit_array, test_bit_array, __LINE__);
}

static void TestBitArrayResetAll()
{
	bitarray_t test_bit_array = 568976;
	bitarray_t control_bit_array = 0;
	
	test_bit_array = BitArrayResetAll(test_bit_array);
	
	TestBitArray(control_bit_array, test_bit_array, __LINE__);
}

static void TestBitArraySetAll()
{
	bitarray_t test_bit_array = 1;
	bitarray_t control_bit_array = SIZE_MAX;
	
	test_bit_array = BitArraySetAll(test_bit_array);
	
	TestBitArray(control_bit_array, test_bit_array, __LINE__);
}

static void TestBitArrayFlip()
{
	bitarray_t test_bit_array = 7;
	size_t test_index = 4;
	bitarray_t control_bit_array = 15;

	test_bit_array = BitArrayFlip(test_bit_array, test_index);
	
	TestBitArray(control_bit_array, test_bit_array, __LINE__);
}

static void TestBitArrayCountOn()
{
	bitarray_t test_bit_array = 7;
	size_t test_count = 0;
	size_t control_count = 3;
	
	test_count = BitArrayCountOn(test_bit_array);

	TestSizeT(control_count, test_count, __LINE__);
}

static void TestBitArrayCountOff()
{
	bitarray_t test_bit_array = 7;
	size_t test_count = 0;
	size_t control_count = 61;
	
	test_count = BitArrayCountOff(test_bit_array);

	TestSizeT(control_count, test_count, __LINE__);
}

static void TestBitArrayToString()
{
	bitarray_t test_bit_array = 4685427;
	char *buffer = NULL;
	
	buffer = (char *)malloc(sizeof(size_t) * BYTE_SIZE + 1);
	
	buffer = BitArrayToString(test_bit_array, buffer);
			
	printf("Test BitArrayToString:\n");
	PrintInBinary64Bits(test_bit_array);
	printf("Test    %s\n", buffer);
	
	free(buffer);
	buffer = NULL;
}

static void TestBitArrayRotateLeft()
{
	bitarray_t test_bit_array = ((bitarray_t)1 << 63);
	size_t offset = 127;
	bitarray_t control_bit_array = ((bitarray_t)1 << 62);

	test_bit_array = BitArrayRotateLeft(test_bit_array, offset);
	
	TestBitArray(control_bit_array, test_bit_array, __LINE__);
}

static void TestBitArrayRotateRight()
{
	bitarray_t test_bit_array = 16;
	size_t offset = 1;
	bitarray_t control_bit_array = 8;

	test_bit_array = BitArrayRotateRight(test_bit_array, offset);
	
	TestBitArray(control_bit_array, test_bit_array, __LINE__);
}

static void TestBitArrayMirror()
{
	bitarray_t test_bit_array = 7;
	size_t offset = 3;
	bitarray_t control_bit_array = BitArrayRotateRight(test_bit_array, offset);
		
	test_bit_array = BitArrayMirror(test_bit_array);

	TestBitArray(control_bit_array, test_bit_array, __LINE__);
}

static void TestBitArrayCountOnLUT()
{
	bitarray_t test_bit_array = 255;
	size_t test_count = 0;
	size_t control_count = 8;
	
	test_count = BitArrayCountOnLUT(test_bit_array);
	
	TestSizeT(control_count, test_count, __LINE__);
}

static void TestBitArrayMirrorLUT()
{
	bitarray_t test_bit_array = 7;
	size_t offset = 3;
	bitarray_t control_bit_array = BitArrayRotateRight(test_bit_array, offset);
		
	test_bit_array = BitArrayMirrorLUT(test_bit_array);

	TestBitArray(control_bit_array, test_bit_array, __LINE__);
}
