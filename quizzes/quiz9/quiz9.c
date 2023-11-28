/*******************************************************************************
*Auther: Arieh Farber
*******************************************************************************/
#include <string.h> /*strlen*/

#include "quiz9.h"

char *RemoveSpaces(char *str)
{
	size_t i = 0;
	size_t j = 0;
	char *str_start = NULL;
	
	str_start = str;

	while (str[j] == ' ' || str[j] == '\t')
	{
		j++;
	}
	
	while ('\0' != str[j]) 
	{
		str[i] = str[j];
		i++;
		j++;
		if (str[j] == ' ')
		{
			while (str[j + 1] == ' ')
			{
				j++;
			}
		}
	}
	
	while (str[i - 1] == ' ' || str[i - 1] == '\t')
	{
		i--;
	}
	
	str[i] = '\0';
	
	return (str_start);
}
