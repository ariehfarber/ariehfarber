/***********************************************************************************
*Author: Arieh Farber
*Reviewer: Yarden Shai
*Date: 9/11/2023
***********************************************************************************/

#include <assert.h> /*assert */
#include <stddef.h> /*size_t */
#include <stdlib.h> /*malloc */
#include <ctype.h>  /*tolower*/
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

int StrCmp(const char *str1, const char *str2)
{
	assert(NULL != str1);
	assert(NULL != str2);
	
	while(*str1 == *str2 && '\0' != *str1)
	{
		str1++;
		str2++;	
	}
			
	return (*str1 - *str2);
}

int StrNCmp(const char *str1, const char *str2, size_t n)
{
	assert(NULL != str1);
	assert(NULL != str2);
	
	if(n == 0) 
	{
        	return (0); 	
	}

	while('\0' != *str1 && '\0' != *str2 && n > 0 && *str1 == *str2)
	{
		str1++;
		str2++;	
		n--;
	}
	
	return (*str1 - *str2);
}

int StrCaseCmp(const char *str1, const char *str2)
{

	assert(str1 != NULL);
	assert(str2 != NULL);

	while (*str1 != '\0' && *str2 != '\0' && tolower(*str1) == tolower(*str2)) 
	{
		str1++;
		str2++;
	}
	return (tolower(*str1) - tolower(*str2));
}

char *StrCpy(char *destination, const char *source)
{
	char *origin = NULL;
	
	assert(NULL != source);
	assert(NULL != destination);
	
	origin = destination;
	
	while('\0' != *source)
	{
		*destination = *source;
		source++;
		destination++;
	}
	*destination = '\0';
	
	return (origin);
}

char *StrNCpy(char *destination, const char *source, size_t n)
{
	char *origin = destination;
	
	assert(NULL != source);
	assert(NULL != destination);
	
	while('\0' != *source && n > 0)
	{
		*destination = *source;
		source++;
		destination++;
		n--;
	}

	/*Paddeing The rest of the memmory in destination with null characters*/
	while(n > 0)
	{
		*destination = '\0';
		destination++;
		n--;
	}
	
	return (origin);
}

char *StrChr(const char *str, int sign)
{
	assert(NULL != str);
	
	while('\0' != *str && *str != sign)
	{
		str++;
	}
	
	if(*str == sign)
	{
		return((char *)str);
	}
	
	return (NULL);
}

char *StrDup(const char *str)
{
	char *duplicated = NULL;
	
	assert(NULL != str);
	
	duplicated = (char *)malloc(StrLen(str) + 1);
	assert(NULL != duplicated);
	
	duplicated = StrCpy(duplicated ,str);
	
	return (duplicated);
}

char *StrCat(char *destination, const char *source)
{
	char *origin = NULL;
	
	assert(NULL != destination);
	assert(NULL != source);

	origin = destination;	
	
	/*Moving the pointer to the end of destination*/
	destination += StrLen(destination);
	
	destination = StrCpy(destination ,source);
	
	return (origin);
}

char *StrNCat(char *destination, const char *source, size_t n)
{
	char *origin = NULL;
	
	assert(NULL != destination);
	assert(NULL != source);
	
	origin = destination;
	
	destination += StrLen(destination);
	
	while('\0' != *source && n > 0)
	{
		*destination = *source;
		destination++;
		source++;
		n--;
	}
	*destination = '\0';
	
	return (origin);
}

char *StrStr(const char *haystack, const char *needle)
{
	char *pointer = NULL; 
	
	assert(NULL != haystack);
	assert(NULL != needle);
	
	while('\0' != *haystack)
	{
		if(*needle == *haystack)
		{
			/*Saving a pointer to the beginning of needle*/
			pointer = (char *)haystack - 1;
			while(*needle == *haystack)
			{
				needle++;
				haystack++;	
			}
			if('\0' == *needle)
			{
				return (pointer);
			}
		}
		haystack++;		 
	}
	
	return (NULL);		
}


size_t StrSpn(const char *s, const char *accept)
{
	size_t count = 0;
	
	assert(NULL != s);
	assert(NULL != accept);
	
	while('\0' != *s && NULL != StrChr(accept, *s))
	{
			s++;
			count++;	
	}
	
	return (count);
}



























