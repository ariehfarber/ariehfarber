/*******************************************************************************
*Author: Arieh Farber 
*Reviewer:  
*Date: 
*******************************************************************************/
#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h> /* size_t */

/******************************************************************************
*Description: Sorts the array using the bubble sort algorithm.
*Arguments: arr - and array of ints.
*			arr_size - the size of the array
*Return Value: None.
*Time Complexity: O(n^2)
*Space Complexity: O(1)
*Notes: If arr is NULL it will lead to undefined behavior.
******************************************************************************/
void BubbleSort(int *arr, size_t arr_size);

/******************************************************************************
*Description: Sorts the array using the selection sort algorithm.
*Arguments: arr - and array of ints.
*			arr_size - the size of the array
*Return Value: None.
*Time Complexity: O(n^2)
*Space Complexity: O(1)
*Notes: If arr is NULL it will lead to undefined behavior.
******************************************************************************/
void SelectionSort(int *arr, size_t arr_size);

/******************************************************************************
*Description: Sorts the array using the insertion sort algorithm.
*Arguments: arr - and array of ints.
*			arr_size - the size of the array
*Return Value: None.
*Time Complexity: O(n^2)
*Space Complexity: O(1)
*Notes: If arr is NULL it will lead to undefined behavior.
******************************************************************************/
void InsertionSort(int *arr, size_t arr_size);

/******************************************************************************
*Description: Sorts the array using the counting sort algorithm.
*Arguments: arr - and array of ints.
*			arr_size - the size of the array
*Return Value: (0)  - Success
*			   (-1) - Error
*Time Complexity: O(n + k)
*Space Complexity: O(k)
*Notes: If arr is NULL it will lead to undefined behavior.
*       k is the number of possible values.
******************************************************************************/
int CountingSort(int *arr, size_t arr_size);

/******************************************************************************
*Description: Sorts the array using the RadixSort algorithm.
*Arguments: arr - and array of ints.
*			arr_size - the size of the array
*Return Value: (0)  - Success
*			   (-1) - Error
*Time Complexity: O(n * k)
*Space Complexity: O(n + k)
*Notes: If arr is NULL it will lead to undefined behavior.
*       k is the number of digits in the largest number in the array.
******************************************************************************/
int RadixSort(int *arr, size_t arr_size);

#endif /*__SORT_H__*/
