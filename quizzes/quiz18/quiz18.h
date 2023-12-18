/*******************************************************************************
*Auther: Arieh Farber
*******************************************************************************/
#ifndef  __QUIZ18_H__
#define __QUIZ18_H__

#include <stddef.h> /*size_t*/

/*******************************************************************************
*Description: Converts an array of ints (32 bits) to an array of longs (64 bits)
*			  by summing adjacent pairs. Without using dynamic allocation.
*Notes: Assumes the original array's size is an even number. 
*******************************************************************************/
long *SumIntPairsToLongs(int ints[], size_t num_of_elements);

#endif /*__QUIZ18_H__*/

