/*******************************************************************************
*Auther: Arieh Farber
*Reviewr: Igal Maikis
*Date: 5/11/2023
*******************************************************************************/
#ifndef __WS1_H__
#define __WS1_H__

/*******************************************************************************
*Description: Creats a Null terminated"hello, world!" string using 
*			  hexadecimal values.
*******************************************************************************/
char *HexadecimalHelloWorld(void);

/*******************************************************************************
*Description: Calculates 10 to the Power of n.
*******************************************************************************/
double PowerBaseTen(signed int exponent);

/*******************************************************************************
*Description: Flips the digits of a provided integer.
*******************************************************************************/
int FlipDigits(signed int number);

/*******************************************************************************
*Description: Swap two postive integer variables.
*******************************************************************************/
void Swap(signed int *var1, signed int *var2);

#endif /*__WS1_H__*/ 
