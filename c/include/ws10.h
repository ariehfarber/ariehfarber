/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Ben Cohen
*Date: 27/11/2023
*******************************************************************************/
#ifndef  __WS10_H__
#define __WS10_H__

#include <stddef.h> /*size_t*/

/*******************************************************************************
*Description: Fills the first n bytes of the memory area pointed to by str
*			  with the constant byte c.
*Return values: A pointer to the memory area str.
*Notes: If n is bigger than the total byte size of str it will lead to 
*		undefined behaviour.
*******************************************************************************/
void *MemSet(void *str, int c, size_t n);

/*******************************************************************************
*Description: Copies n bytes from memory area src to memory area dest.
*Return values: A pointer to dest.
*Notes: The memory areas must not overlap.
*******************************************************************************/
void *MemCpy(void *dest, const void *src, size_t n);

/*******************************************************************************
*Description:  Copies n bytes from memory area src to memory area dest.
*			   The memory areas may overlap: copying takes place as though
*			   the bytes in src are first copied  into  a temporary  array
*			   that does not overlap src or dest, and the bytes are then 
*			   copied from the temporary array to dest.
*Return values: A pointer to dest.
*******************************************************************************/
void *MemMove(void *dest, const void *src, size_t n);

#endif /*__WS10_H__*/
