/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Artur Livshits
*Date: 29/11/2023
*******************************************************************************/
#include <stdint.h> /*SIZE_MAX*/
#include <limits.h> /*CHAR_BIT*/
#include <assert.h> /*assert  */

#include "bitarray.h"

#define BYTE_SIZE CHAR_BIT
#define SIZE_T_BITS (sizeof(bitarray_t) * BYTE_SIZE)
#define MASK_ONE 1
#define OCTET_VALUES 256

static int bit_look_up_table[OCTET_VALUES];
static int mirror_look_up_table[OCTET_VALUES];

static void BitArrayInitializeCountLUT();
static void BitArrayInitializeMirrorLUT();

int BitArrayGetVal(bitarray_t b_arr, size_t index)
{
	assert((SIZE_T_BITS - 1) >= index);
	
	return ((b_arr >> (index - 1)) & MASK_ONE);
}

bitarray_t BitArraySetBit(bitarray_t b_arr, size_t index, int bool_val)
{
	assert((SIZE_T_BITS - 1) >= index);
	
	if (1 == bool_val)
	{
		b_arr = BitArraySetOn(b_arr, index);
	}
	else
	{
		b_arr = BitArraySetOff(b_arr, index);
	}
	
	return (b_arr);
}

bitarray_t BitArraySetOn(bitarray_t b_arr, size_t index)
{
	size_t mask = 1;
		
	assert((SIZE_T_BITS - 1) >= index);
 
	mask <<= (index - 1); 
	
	b_arr |= mask;
	
	return (b_arr);
}

bitarray_t BitArraySetOff(bitarray_t b_arr, size_t index)
{
	size_t mask = 1;
		
	assert((SIZE_T_BITS - 1) >= index);
 
	mask <<= (index - 1); 
	
	b_arr &= ~mask;
	
	return (b_arr);	
}

bitarray_t BitArrayResetAll(bitarray_t b_arr)
{
	b_arr = 0;
	
	return (b_arr);	
}

bitarray_t BitArraySetAll(bitarray_t b_arr)
{
	b_arr |= SIZE_MAX;
	
	return (b_arr);	
}

bitarray_t BitArrayFlip(bitarray_t b_arr, size_t index)
{
	size_t mask = 1;
		
	assert((SIZE_T_BITS - 1) >= index);
 
	mask <<= (index - 1);
	
	b_arr ^= mask;
	
	return (b_arr);	
}

size_t BitArrayCountOn(bitarray_t b_arr)
{
	size_t set_bit_counter = 0;
	
	while (0 != b_arr)
	{
		b_arr &= (b_arr - 1);
		set_bit_counter++;
	}
	
	return (set_bit_counter);
}

size_t BitArrayCountOff(bitarray_t b_arr)
{
	size_t off_bit_counter = SIZE_T_BITS;
	
	off_bit_counter -= BitArrayCountOn(b_arr);
	
	return (off_bit_counter);
}

char *BitArrayToString(bitarray_t b_arr, char *buffer)
{
    size_t bit_counter = SIZE_T_BITS;
    char *buffer_start = buffer;
    int digit = 0;

    assert(NULL != buffer);

    while (0 != bit_counter) 
    {
        digit = (b_arr >> (bit_counter - 1)) & MASK_ONE;
        *buffer = (char)digit + '0';
        bit_counter--;
        buffer++;
    }

    *buffer = '\0';

    return buffer_start;
}

bitarray_t BitArrayRotateLeft(bitarray_t b_arr, size_t offset)
{
	bitarray_t mask = 1;
	bitarray_t hold_value = 0;
	
	offset %= SIZE_T_BITS;
	
	while (0 != offset)
	{
		hold_value = (b_arr & (mask << (SIZE_T_BITS - 1))) >> (SIZE_T_BITS - 1);
		b_arr <<= 1;
		b_arr |= hold_value;
		offset--;
	}

	return (b_arr);	
}

bitarray_t BitArrayRotateRight(bitarray_t b_arr, size_t offset)
{
	bitarray_t mask = 1;
	bitarray_t hold_value = 0;
	
	offset %= SIZE_T_BITS;
	
	while (0 != offset)
	{
		hold_value = (b_arr & mask) << (SIZE_T_BITS - 1);
		b_arr >>= 1;
		b_arr |= hold_value;
		offset--;
	}

	return (b_arr);	
}

bitarray_t BitArrayMirror(bitarray_t b_arr)
{
	bitarray_t mirror_b_arr = 0;
	bitarray_t i = 0;
	
	for (i = 0; i < SIZE_T_BITS; i++)
	{
		mirror_b_arr |= (((b_arr >> i) & 1) << (SIZE_T_BITS - 1 - i));
	}
	
	return (mirror_b_arr);
}

size_t BitArrayCountOnLUT(bitarray_t b_arr)
{
	size_t bit_counter = 0;
	
	BitArrayInitializeCountLUT();
	
	while (0 != b_arr)
	{
		bit_counter += bit_look_up_table[b_arr & (OCTET_VALUES - 1)];
		b_arr >>= BYTE_SIZE;
	}
	
	return (bit_counter);
}

bitarray_t BitArrayMirrorLUT(bitarray_t b_arr)
{
	bitarray_t i = 0;
	bitarray_t mirror_b_arr = 0;
	
	BitArrayInitializeMirrorLUT();
	
	for (i = 0; i < (BYTE_SIZE - 1); i++)
	{
		mirror_b_arr |= mirror_look_up_table[b_arr & (OCTET_VALUES - 1)];
		mirror_b_arr <<= BYTE_SIZE;
		b_arr >>= BYTE_SIZE;
	}
	
	return (mirror_b_arr);
}

static void BitArrayInitializeCountLUT()
{
	int i = 0;
	
	for (i = 0; i < OCTET_VALUES; i++)
	{
		bit_look_up_table[i] = (i & MASK_ONE) + bit_look_up_table[i / 2];
	} 
}

static void BitArrayInitializeMirrorLUT()
{
	int number = 0;
	int i = 0;
	int mirror_num = 0;

	for (number = 0; number < OCTET_VALUES; number++)
	{
		mirror_num = 0;
		for (i = 0; i < BYTE_SIZE; i++)
		{
			mirror_num |= (((number >> i) & MASK_ONE) << (BYTE_SIZE - 1 - i));
		}
		mirror_look_up_table[number] = mirror_num;
	}
}
