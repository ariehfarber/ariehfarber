/*******************************************************************************
*Auther: Arieh Farber
*******************************************************************************/
#include "quiz10.h"

int *MaxSubArray(int *arr, int arr_size, int *buffer)
{
	int i = 0;
	int current_sum = 0;
	int max_sum = 0;
	int first_index = 0;
	int temp_first_index = 0;
	
	for (i = 0; i < arr_size; i++)
	{
		current_sum += arr[i];
		
		if (current_sum > max_sum) 
		{
			max_sum = current_sum;
			first_index = temp_first_index;
			buffer[2] = i;
		}
		
        if (current_sum < 0) 
        {
        	current_sum = 0;
        	temp_first_index = i + 1;
        }
	}
	
    buffer[0] = max_sum;
    buffer[1] = first_index;
    
    return (buffer);
}
