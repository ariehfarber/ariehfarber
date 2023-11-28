/*******************************************************************************
*Auther: Arieh Farber
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <string.h> /*strlen*/

int IsStringRotation(char *str1, char *str2);

int main()
{
	char *string1 = "123456";
	char *string2 = "345612";
	int result = 0;
	
	result = IsStringRotation(string1, string2);
	
	printf("%d\n", result);
	
	return (0);
}

int IsStringRotation(char *str1, char *str2)
{
	int i = 0, j = 0;
	int size1 = 0, size2 = 0;

	size1 = strlen(str1);
	size2 = strlen(str2);
	
	if (size1 != size2)
	{
		return (0);
	}
	
	for (i = 0; i < size1; i++)
	{
		for (j = 0; j < size1; j++)
		{
			if (str1[(i + j) % size1] != str2[j])
			{
				break;
			}
		}	
		if (j == size1)
		{
			return (1);	
		}		
	}
	
	return (0);
}





