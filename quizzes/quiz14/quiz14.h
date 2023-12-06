/*******************************************************************************
*Auther: Arieh Farber
*******************************************************************************/
#ifndef  __QUIZ14_H__
#define __QUIZ14_H__

#include <stddef.h> /*size_t*/

/*******************************************************************************
*Description: The function can be called many times. When the value of the
* 			  argument char is 0 it prints the maximum number of occurrences
* 			  of the same character in all previous calls 
*Notes:		  The count starts from the beginning or from the last 
*			  time 0 was passed.
*******************************************************************************/
void CharacterCounter(char c);

/*******************************************************************************
*Description: Counts the number of set bits in a long, using a loop. 
*			  The number of times the loop executes is equal to 
*			  the number of set bits.
*******************************************************************************/
size_t BitCounter(long num);

#endif /*__QUIZ14_H__*/

