/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Yarden Shai
*Date: 28/11/2023
*******************************************************************************/
#ifndef _WS11_
#define _WS11_

#include <stddef.h> /*size_t*/

static const int one = 1;
#define IS_LITTLE_ENDIAN (*(unsigned char *)&one == 1 ? 1 : 0)

/*******************************************************************************
*Description: Converts the initial portion of the string pointed to by
*			  str to an integer.
*Return values: The converted value. 
*				If the initial portion is non numerical it returns 0.
*Note: The return value is undefined in the case of an overflow.
*******************************************************************************/
int Atoi(const char *str);

/*******************************************************************************
*Description: Converts the initial portion of the string pointed to by
*			  str to an integer in the base specified by the argument.
*Return values: The converted value. 
*				If the initial portion is non numerical it returns 0.
*Note: The return value is undefined in the case of an integer overflow.
*******************************************************************************/
int AtoiAnyBase(const char *str, int base);

/*******************************************************************************
*Description: Converts an integer to a null-terminated string.
*******************************************************************************/
char* Itoa(int num, char* buffer);

/*******************************************************************************
*Description: Converts an integer number to a null-terminated string in the
*			  base specified by the argument.
*******************************************************************************/
char* ItoaAnyBase(int num, char* buffer, int base);

/*******************************************************************************
*Description:
*Return values: 
*Notes: 
*******************************************************************************/
void PrintArrayOfChars(char *str1, char *str2 ,char *str3, size_t size1, 
					   size_t size2, size_t size3);

/*******************************************************************************
*Description:
*Return values: 
*Notes: 
*******************************************************************************/
int IsLittleEndian(void);

#endif /*_WS11_*/
