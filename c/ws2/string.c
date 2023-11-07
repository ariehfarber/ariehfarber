/*Functions*/

#include <assert.h> /*included for assert() function*/
#include <stddef.h> /*included for size_t variable type*/
#include "string.h"

size_t StrLen(const char *str)
{
	size_t i = 0;
	
	assert(str != NULL);
	
	while(*str++ != '\0')
	{
		i++;
	}
	
	return (i);
}

int StrCmp(const char *str1, const char *str2)
{
	assert(str1 != NULL && str2 != NULL);
	
	while((*str1 == *str2) && (*str1 != '\0'))
	{
		str1++;
		str2++;	
	}
	
		if(*str1 == *str2)
		{
		return 0;
		}
		else if(*str1 == '\0')
		{
		return -1;
		}
		else if(*str2 == '\0')
		{
		return 1;
		}

		
	return *str1 - *str2;
}


