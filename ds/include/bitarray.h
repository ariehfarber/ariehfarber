/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#ifndef _BITARRAY_H_
#define _BITARRAY_H_

#include <stddef.h> /*size_t*/

typedef size_t bitarray_t;

int BitArrayGetVal(bitarray_t b_arr, size_t index);

bitarray_t BitArraySetBit(bitarray_t b_arr, size_t index, int bool_val);

bitarray_t BitArraySetOn(bitarray_t b_arr, size_t index);

bitarray_t BitArraySetOff(bitarray_t b_arr, size_t index);

bitarray_t BitArrayResetAll(bitarray_t b_arr);

bitarray_t BitArraySetAll(bitarray_t b_arr);

bitarray_t BitArrayFlip(bitarray_t b_arr, size_t index);

size_t BitArrayCountOn(bitarray_t b_arr);

size_t BitArrayCountOff(bitarray_t b_arr);

char *BitArrayToString(bitarray_t b_arr, char *buffer);

bitarray_t BitArrayRotateLeft(bitarray_t b_arr, size_t offset);

bitarray_t BitArrayRotateRight(bitarray_t b_arr, size_t offset);

bitarray_t BitArrayMirror(bitarray_t b_arr);

#endif	/* _BITARRAY_H_*/
