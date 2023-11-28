/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Dvir Monajem
*Date: 22/11/2023
*******************************************************************************/
#ifndef  __WS8_H__
#define __WS8_H__

#include <stddef.h> /*size_t*/

#define ELEMENT_NUM 5

typedef void (*PFnPrint)(size_t);
typedef void (*PFnAdd)(size_t *, int);
typedef void (*PFnClean)(size_t *);

typedef struct element
{
	size_t data;
	PFnPrint PrintValue;
	PFnAdd AddNumber;
	PFnClean CleanValue;
} element_t;

/*******************************************************************************
*Description: The following functions can be used to set elements into
*			  a array of mixed data types.
*			  SetInt - used for setting integer numbers.
*			  SetFloat - used for setting float numbers.
*			  SetString - used for setting strings.
*******************************************************************************/
void SetInt(element_t *target, int int_number); 
void SetFloat(element_t *target, float float_number); 
void SetString(element_t *target, char *str); 

/*******************************************************************************
*Description: Prints the array to the screen.
*******************************************************************************/
void PrintElements(element_t *my_elements);

/*******************************************************************************
*Description: The following function can be used to add a number to 
*			  each one of the array elements based on their data type:
*	      	  Int - adds an int number.
*	      	  Float - adds a float number.
*	     	  Char - concatenates the number to the end of the string.
*******************************************************************************/
void AddElements(element_t *my_elements, int int_num);
/*******************************************************************************
*Description: The following function must be used at the end to free all
			  the memory used by the program.
*******************************************************************************/
void CleanElements(element_t *my_elements);

#endif /*__WS8_H__*/
