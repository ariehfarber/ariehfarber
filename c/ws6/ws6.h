/***********************************************************************************
*Author: Arieh Farber 
*Reviewer: Artur Livshits
*Date: 
***********************************************************************************/

#ifndef  __WS6_H__
#define __WS6_H__

/***********************************************************************************
*Exercise 1
*Description: returns the result of the equation x*(2^y)
***********************************************************************************/
long Pow2(unsigned int x, unsigned int y);

/***********************************************************************************
*Exercise 2
*Description: checks if a number is a power of 2
*Retuern values: returns 1 if n is a power of 2. Otherwise it returns 0
*Notes: both functions perform the same task with differnet implementations 
***********************************************************************************/
unsigned int IsPow2WithLoop(unsigned int n);
unsigned int IsPow2NoLoop(unsigned int n);

/***********************************************************************************
*Exercise 3
*Description: adds 1 to a number without using arithmetic operators
*Retuern values: n + 1
***********************************************************************************/
int AddOne(int n);

/***********************************************************************************
*Exercise 4
*Description: receives an array of numbers and prints the ones that have 
*	      exactly 3 bits "on" (set to 1)
***********************************************************************************/
void ThreeBitsOn(unsigned int *arr, unsigned int size);

/***********************************************************************************
*Exercise 5
*Description: takes a number up to 1 Byte and "mirrors" its bits
*Notes: both functions perform the same task with differnet implementations 
*Notes: number range must be between 0 to 255
***********************************************************************************/
unsigned char ByteMirrorWithLoop(unsigned char n);
unsigned char ByteMirrorNoLoop(unsigned char n);

/***********************************************************************************
*Exercise 6
*Description: receives a number and checks if the 2nd and 6th bits are on
*Notes: number range must be between 0 to 255
***********************************************************************************/
int IsBitsTwoAndSix(unsigned char n);
/***********************************************************************************
*Description: receives a number and checks if the 2nd and/or 6th bits are on
*Notes: number range must be between 0 to 255
***********************************************************************************/
int IsBitsTwoOrSix(unsigned char n);
/***********************************************************************************
*Description: receives a number and swaps between its 3rd and 5th bits
*Retuern values: the number with the swaped bits
*Notes: number range must be between 0 to 255
***********************************************************************************/
unsigned char SwapBitsThreeAndFive(unsigned char n);

/***********************************************************************************
*Exercise 7
*Description: receives a positive number and returns the closest number that is 
*	      divisible by 16 without a remainder
***********************************************************************************/
unsigned int ClosestDivisibleBy16(unsigned int n);

/***********************************************************************************
*Exercise 8
*Description: swap 2 variables without using a third variable
***********************************************************************************/
void SwapWithBits(int *p1, int *p2);

/***********************************************************************************
*Exercise 9
*Description: returns the number of bits in an integer
*Notes: both functions perform the same task with differnet implementations 
***********************************************************************************/
int NumberOfBitsWithLoop(int n);
int NumberOfBitsNoLoop(int n);

/***********************************************************************************
*Exercise 10
*Description: receives a float type number and prints its bits
***********************************************************************************/
void FloatInBits(float f_num);

#endif /*__WS6_H__*/














