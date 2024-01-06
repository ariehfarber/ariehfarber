/*******************************************************************************
*Author: Arieh Farber 
*******************************************************************************/
#ifndef __DS_UTILS_H__
#define __DS_UTILS_H__

#include <stddef.h> /*size_t*/

#define TRUE       1
#define FALSE      0
#define SUCCESS    0
#define ASCII_SIZE 256
#define EPSILON    0.0001
#define WORD_SIZE  sizeof(size_t)

/******************************************************************************
*Description: Compares 2 int variables
*Parameters: want variable, got variable and the __LINE__ macro.
*Notes: Prints an error message with the line number if the values differ.
******************************************************************************/
void TestInt(int want, int got, int line);

/******************************************************************************
*Description: Compares two unsigned int variables.
*Parameters: want variable, got variable, and the __LINE__ macro.
*Notes: Prints an error message with the line number if the values differ.
******************************************************************************/
void TestUnsignedInt(unsigned int want, unsigned int got, int line);

/******************************************************************************
*Description: Compares between the size of got variable and the size
*			  of the want variable. If the diffarence between the variables
*             is bigger than EPSILON it prints an error message 
*             with the line number.
*Parameters: want variable, got variable, and the __LINE__ macro.
*Notes: Prints an error message with the line number if the values differ.
******************************************************************************/
void TestDouble(double want, double got, int line);

/******************************************************************************
*Description: Compares two long variables.
*Parameters: want variable, got variable, and the __LINE__ macro.
*Notes: Prints an error message with the line number if the values differ.
******************************************************************************/
void TestLong(long want, long got, int line);

/******************************************************************************
*Description: Compares two size_t variables.
*Parameters: want variable, got variable, and the __LINE__ macro.
*Notes: Prints an error message with the line number if the values differ.
******************************************************************************/
void TestSizeT(size_t want, size_t got, int line);

/******************************************************************************
*Description: Compares two pointer variables.
*Parameters: want pointer, got pointer, and the __LINE__ macro.
*Return Value: None.
*Notes:Prints an error message with the line number if the pointers differ.
******************************************************************************/
void TestPtr(void *want, void *got, int line);

/******************************************************************************
*Description: Compares two null-terminated char arrays (strings).
*Parameters: want string, got string, and the __LINE__ macro.
*Notes: Prints an error message with the line number if the values differ.
******************************************************************************/
void TestChar(char *want, char *got, int line);

/******************************************************************************
*Description: Compares two char arrays (strings) up to n characters.
*Parameters: want string, got string, number of characters to 
*			 compare (n), and the __LINE__ macro. 
*Notes: Compares each character up to n; 
*		prints an error message with the line number if any character differs.
******************************************************************************/
void TestNChar(char *want, char *got, size_t n, int line);

/******************************************************************************
*Description: Compares two unsigned char variables.
*Parameters: want char, got char, and the __LINE__ macro.
*Notes: Prints an error message with the line number if the values differ.
******************************************************************************/
void TestUnsignedChar(unsigned char want, unsigned char got, int line);

#endif	/*__DS_UTILS_H__*/
