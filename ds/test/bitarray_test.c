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
#include "ds_utils.h" /*TestInt, TestSizeT*/

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
static void TestBitArray(bitarray_t want, bitarray_t got, int line);
static void PrintInBinary64Bits(bitarray_t number);


static void TestBitArrayGetVal()
{
	bitarray_t got_bit_array = 16;
	size_t got_index = 5;
	int got_val = 0;
	int want_val = 1;
	
	got_val = BitArrayGetVal(got_bit_array, got_index);
	
	TestInt(want_val, got_val, __LINE__);
}

static void TestBitArraySetBit()
{
	bitarray_t got_bit_array = 7;
	size_t got_index = 4;
	int bool_val = 1;
	bitarray_t want_bit_array = 15;
	
	got_bit_array = BitArraySetBit(got_bit_array, got_index, bool_val);
	
	TestBitArray(want_bit_array, got_bit_array, __LINE__);
}

static void TestBitArrayResetAll()
{
	bitarray_t got_bit_array = 568976;
	bitarray_t want_bit_array = 0;
	
	got_bit_array = BitArrayResetAll(got_bit_array);
	
	TestBitArray(want_bit_array, got_bit_array, __LINE__);
}

static void TestBitArraySetAll()
{
	bitarray_t got_bit_array = 1;
	bitarray_t want_bit_array = SIZE_MAX;
	
	got_bit_array = BitArraySetAll(got_bit_array);
	
	TestBitArray(want_bit_array, got_bit_array, __LINE__);
}

static void TestBitArrayFlip()
{
	bitarray_t got_bit_array = 7;
	size_t got_index = 4;
	bitarray_t want_bit_array = 15;

	got_bit_array = BitArrayFlip(got_bit_array, got_index);
	
	TestBitArray(want_bit_array, got_bit_array, __LINE__);
}

static void TestBitArrayCountOn()
{
	bitarray_t got_bit_array = 7;
	size_t got_count = 0;
	size_t want_count = 3;
	
	got_count = BitArrayCountOn(got_bit_array);

	TestSizeT(want_count, got_count, __LINE__);
}

static void TestBitArrayCountOff()
{
	bitarray_t got_bit_array = 7;
	size_t got_count = 0;
	size_t want_count = 61;
	
	got_count = BitArrayCountOff(got_bit_array);

	TestSizeT(want_count, got_count, __LINE__);
}

static void TestBitArrayToString()
{
	bitarray_t got_bit_array = 4685427;
	char *buffer = NULL;
	
	buffer = (char *)malloc(sizeof(size_t) * CHAR_BIT + 1);
	
	buffer = BitArrayToString(got_bit_array, buffer);

	PrintInBinary64Bits(got_bit_array);
	printf("Got  %s\n", buffer);
	
	free(buffer);
	buffer = NULL;
}

static void TestBitArrayRotateLeft()
{
	bitarray_t got_bit_array = ((bitarray_t)1 << 63);
	size_t offset = 127;
	bitarray_t want_bit_array = ((bitarray_t)1 << 62);

	got_bit_array = BitArrayRotateLeft(got_bit_array, offset);
	
	TestBitArray(want_bit_array, got_bit_array, __LINE__);
}

static void TestBitArrayRotateRight()
{
	bitarray_t got_bit_array = 16;
	size_t offset = 1;
	bitarray_t want_bit_array = 8;

	got_bit_array = BitArrayRotateRight(got_bit_array, offset);
	
	TestBitArray(want_bit_array, got_bit_array, __LINE__);
}

static void TestBitArrayMirror()
{
	bitarray_t got_bit_array = 7;
	size_t offset = 3;
	bitarray_t want_bit_array = BitArrayRotateRight(got_bit_array, offset);
		
	got_bit_array = BitArrayMirror(got_bit_array);

	TestBitArray(want_bit_array, got_bit_array, __LINE__);
}

static void TestBitArrayCountOnLUT()
{
	bitarray_t got_bit_array = 255;
	size_t got_count = 0;
	size_t want_count = 8;
	
	got_count = BitArrayCountOnLUT(got_bit_array);
	
	TestSizeT(want_count, got_count, __LINE__);
}

static void TestBitArrayMirrorLUT()
{
	bitarray_t got_bit_array = 7;
	size_t offset = 3;
	bitarray_t want_bit_array = BitArrayRotateRight(got_bit_array, offset);
		
	got_bit_array = BitArrayMirrorLUT(got_bit_array);

	TestBitArray(want_bit_array, got_bit_array, __LINE__);
}

static void TestBitArray(bitarray_t want, bitarray_t got, int line)
{
	if (want != got)
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
	
	size = sizeof(size_t) * CHAR_BIT - 1;
	
	printf("want ");
	for (i = size; i >= 0; --i) 
	{
		binaryDigit = (number >> i) & 1;
		printf("%d", binaryDigit);
	}
	printf("\n");
}
