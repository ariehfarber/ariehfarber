/*******************************************************************************
*Author: Arieh Farber
*Reviewer: Yarden Shai
*Date: 9/11/2023
*******************************************************************************/

#include <assert.h> /*assert */
#include <stddef.h> /*size_t */
#include <stdlib.h> /*malloc */
#include <ctype.h>  /*tolower*/

#include "String.h"

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

	while (*str1 != '\0' && *str2 != '\0') 
	{
		if(tolower(*str1) != tolower(*str2))
		{
			break;
		}
		str1++;
		str2++;
	}
	
	return (tolower(*str1) - tolower(*str2));
}

char *StrCpy(char *dest, const char *src)
{
	char *origin = NULL;
	
	assert(NULL != src);
	assert(NULL != dest);
	
	origin = dest;
	
	while('\0' != *src)
	{
		*dest = *src;
		
		src++;
		dest++;
	}
	*dest = '\0';
	
	return (origin);
}

char *StrNCpy(char *dest, const char *src, size_t n)
{
	char *origin = dest;
	
	assert(NULL != src);
	assert(NULL != dest);
	
	while('\0' != *src && n > 0)
	{
		*dest = *src;
		
		src++;
		dest++;
		n--;
	}

	while(n > 0)
	{
		*dest = '\0';
		
		dest++;
		n--;
	}
	
	return (origin);
}

char *StrChr(const char *str, int c)
{
	assert(NULL != str);
	
	while('\0' != *str && *str != c)
	{
		str++;
	}
	
	if(*str == c)
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
	if(!duplicated)
	{
		return (NULL);
	}
	
	return (StrCpy(duplicated ,str));
}

char *StrCat(char *dest, const char *src)
{
	char *origin = NULL;
	
	assert(NULL != dest);
	assert(NULL != src);

	origin = dest;	
	
	/*Moving the pointer to the end of dest*/
	dest += StrLen(dest);
	
	dest = StrCpy(dest ,src);
	
	return (origin);
}

char *StrNCat(char *dest, const char *src, size_t n)
{
	char *origin = NULL;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	origin = dest;
	
	dest += StrLen(dest);
	
	while('\0' != *src && n > 0)
	{
		*dest = *src;
		
		dest++;
		src++;
		n--;
	}
	*dest = '\0';
	
	return (origin);
}

char *StrStr(const char *haystack, const char *needle)
{
	size_t size = 0; 
	
	assert(NULL != haystack);
	assert(NULL != needle);
	
	size = StrLen(needle) - 1;
	
	while((haystack = StrChr(haystack, (int)*needle)))
	{
		if(0 == StrNCmp(haystack, needle, size))
		{
			return((char *)haystack);
		}
		haystack++;		 
	}
	
	return (NULL);		
}


size_t StrSpn(const char *str, const char *accept)
{
	size_t count = 0;
	
	assert(NULL != str);
	assert(NULL != accept);
	
	while('\0' != *str && NULL != StrChr(accept, *str))
	{
			str++;
			count++;	
	}
	
	return (count);
}



























