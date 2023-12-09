/*******************************************************************************
*Author: Arieh Farber 
*Last Edit: 09/12/2023
*******************************************************************************/
#ifndef __MY_TESTS_H__
#define __MY_TESTS_H__

#include <stddef.h> /*size_t*/

/******************************************************************************
*Description: Compares 2 int variables
*Parameters: A control variable, test variable and the __LINE__ macro.
*Notes: Prints an error message with the line number if the values differ.
******************************************************************************/
void TestInt(int control, int test, int line);

/******************************************************************************
*Description: Compares two unsigned int variables.
*Parameters: A control variable, test variable, and the __LINE__ macro.
*Notes: Prints an error message with the line number if the values differ.
******************************************************************************/
void TestUnsignedInt(unsigned int control, unsigned int test, int line);

/******************************************************************************
*Description: Compares two long variables.
*Parameters: A control variable, test variable, and the __LINE__ macro.
*Notes: Prints an error message with the line number if the values differ.
******************************************************************************/
void TestLong(long control, long test, int line);

/******************************************************************************
*Description: Compares two size_t variables.
*Parameters: A control variable, test variable, and the __LINE__ macro.
*Notes: Prints an error message with the line number if the values differ.
******************************************************************************/
void TestSizeT(size_t control, size_t test, int line);

/******************************************************************************
*Description: Compares two pointer variables.
*Parameters: A control pointer, test pointer, and the __LINE__ macro.
*Return Value: None.
*Notes:Prints an error message with the line number if the pointers differ.
******************************************************************************/
void TestPtr(void *control, void *test, int line);

/******************************************************************************
*Description: Compares two null-terminated char arrays (strings).
*Parameters: A control string, test string, and the __LINE__ macro.
*Notes: Prints an error message with the line number if the values differ.
******************************************************************************/
void TestChar(char *control, char *test, int line);

/******************************************************************************
*Description: Compares two char arrays (strings) up to n characters.
*Parameters: A control string, test string, number of characters to 
*			 compare (n), and the __LINE__ macro. 
*Notes: Compares each character up to n; 
*		prints an error message with the line number if any character differs.
******************************************************************************/
void TestNChar(char *control, char *test, size_t n, int line);

/******************************************************************************
*Description: Compares two unsigned char variables.
*Parameters: A control char, test char, and the __LINE__ macro.
*Notes: Prints an error message with the line number if the values differ.
******************************************************************************/
void TestUnsignedChar(unsigned char ctrl, unsigned char test, int line);

#endif	/*__MY_TESTS_H__*/
