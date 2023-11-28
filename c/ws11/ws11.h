/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#ifndef _WS11_
#define _WS11_

/*place macro here*/

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
void PrintArrOfChars(char *str1, char *str2 ,char *str3, size_t size1, 
					 size_t size2, size_t size3);

/*******************************************************************************
*Description:
*Return values: 
*Notes: 
*******************************************************************************/
int IsLittleEndian(void);

#endif /*_WS11_*/
