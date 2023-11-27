#include <stdio.h> /*printf*/

int *BursaProblem(int *arr,int size);

int main()
{
	int array[8] = {6, 12, 3, 5, 1, 4, 9, 2};
	int size = 0;
	int *ret;
	
	size = sizeof(array) / sizeof(array[0]);
	
	ret = BursaProblem(array, size);
	
 	printf("Max Difference: %d, Buy Index: %d, Sell Index: %d\n", 
 	ret[0], ret[1], ret[2]);
	
	return 0;
}

int *BursaProblem(int *arr,int size)
{
	static int values[3] = {0};
	int i = 0;
	int min_index = 0;
	int max_diff = 0;
	
	max_diff = arr[1] - arr[0];
	
	for (i = 1; i < size; i++) 
	{      
		if (arr[i] - arr[min_index] > max_diff) 
		{
			max_diff = arr[i] - arr[min_index]; 
			values[0] = max_diff;
			values[1] = min_index;
			values[2] = i;
		}                             
		if (arr[i] < arr[min_index])
		{
			min_index = i; 
		}           
	} 
	
	return (values); 
}



