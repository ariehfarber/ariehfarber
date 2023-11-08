/***********************************************************************************
*Auther: Arieh Farber
*Reviewr: Omer Bruker
*Date: 7/11/2023
***********************************************************************************/

#include <assert.h> /*assert*/
#include <stddef.h> /*size_t*/
#include "string.h"

size_t StrLen(const char *str)
{
	size_t i = 0;
	
	assert(NULL != str);
	
	while('\0' != *str++)
	{
		i++;
	}
	
	return (i);
}

int StrCmp(const char *string1, const char *string2)
{
	assert(NULL != string1);
	assert(NULL != string2);
	
	while(*string1 == *string2 && '\0' != *string1 )
	{
		string1++;
		string2++;	
	}
			
	return (*string1 - *string2);
}

char *StrCpy(char *destination, const char *source)
{
	char *origin = destination;
	
	assert(NULL != source);
	
	while('\0' != *source)
	{
		*destination = *source;
		source++;
		destination++;
	}
	*destination = '\0';
	
	return (origin);
}

char *StrNCpy(char *destination, const char *source, size_t iterations)
{
	char *origin = destination;
	
	assert(NULL != source);
	
	while('\0' != *source && 0 != iterations)
	{
		*destination = *source;
		source++;
		destination++;
		iterations--;
	}
	*destination = '\0';
	
	return (origin);
}

int StrNCmp(const char *string1, const char *string2, size_t iterations)
{
	assert(NULL != string1);
	assert(NULL != string2);
	
	while(*string1 == *string2 && '\0' != *string1 && 0 != iterations)
	{
		string1++;
		string2++;	
		iterations--;
	}
			
	return (*string1 - *string2);
}
































