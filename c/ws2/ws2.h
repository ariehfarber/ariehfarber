/*******************************************************************************
*Author: Arieh Farber
*Reviewer: Yarden Shai
*Date: 9/11/2023
*******************************************************************************/
#ifndef  __WS2_H__
#define __WS2_H__

/*******************************************************************************
*Description: Swaps the values of 2 integer variables.
*******************************************************************************/
void IntSwap(int *var1, int *var2);

/*******************************************************************************
*Description: Copies one array on to another
*Notes: The copy of the array must of the same size as the original.
*******************************************************************************/
void CopyArray(int* arry, int* arry_copy, int arry_size);

/*******************************************************************************
*Description: Swaps the values of 2 size_t variables.
*******************************************************************************/
void TSizeSwap(size_t *var1, size_t *var2);

/*******************************************************************************
*Description: Swaps the values of 2 size_t variables by swaping their pointers.
*******************************************************************************/
void PtrSwap(size_t **ptr1, size_t **ptr2);

/*******************************************************************************
*Description: Swaps the values of 2 size_t variables.
*******************************************************************************/
void PtrSwapCombo(size_t **ptr1, size_t **ptr2);

/*******************************************************************************
*Description: Checks if a string is a palindrome
*Retuern values: success - 1
				 fail	 - 0
*******************************************************************************/
int IsPalindrome(const char *str);

#endif /*  __WS2_H__ */
