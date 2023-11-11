/***********************************************************************************
*Author: Arieh Farber
*Date: 11/09/2023
***********************************************************************************/

#ifndef  __WS3_H__
#define __WS3_H__

/*Macro variables*/
#define ROWS 3 
#define COLS 3

/*Functions*/
void AllOneArray(int array[ROWS][COLS]);

void AllTwoArray(int array[][COLS], int rows);

void AllThreeArray(int *arr, int rows, int cols);

void AllFourArray(int (*array)[COLS], int rows);

void AllFiveArray(int **array, int rows, int cols);

#endif /*  __WS3_H__ */
