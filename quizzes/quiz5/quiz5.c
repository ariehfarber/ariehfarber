/*******************************************************************************
*Auther: Arieh Farber
*******************************************************************************/
#include <stdio.h> /*printf*/

int IsSumFound(int *array, int sum, int size);

int main()
{
	int array[] = {0, 2, 3, 4, 7, 12, 16, 25, 36};
	int sum = 19;
	int value = 0;
	int size = sizeof(array) / sizeof(array[0]);
	
	value = IsSumFound(array, sum, size);

	printf("%d \n", value);
	
	return 0;
}

int IsSumFound(int *array, int sum, int size)
{
	int i = 0, j = 0;
	int value = -1;

	j = size - 1;
		
	while (i < j)
	{
		if (array[i] + array[j] < sum )
		{
			i++;
		}	
		if (array[i] + array[j] > sum)
		{
			j--;
		}		
		if (array[i] + array[j] == sum)
		{
			value = 1;
			printf("value of i: %d\n", i);
			printf("value of j: %d\n", j);
			return (value);
		}
	}

	return (value);
}





