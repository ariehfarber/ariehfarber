/***********************************************************************************
*Auther: Arieh Farber
*Reviewr: Omer Bruker
*Date: 7/11/2023
***********************************************************************************/

#include <assert.h> /*assert*/
#include <stddef.h> /*size_t*/
#include <stdlib.h> /*malloc*/
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

int StrNCmp(const char *str1, const char *str2, size_t iterations)
{
	assert(NULL != str1);
	assert(NULL != str2);
	
	if (iterations == 0) 
	{
        	return (0); 	
	}

	while(*str1 == *str2 && '\0' != *str1 && iterations > 0)
	{
		str1++;
		str2++;	
		iterations--;
	}
			
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

int StrCaseCmp(const char *str1, const char *str2)
{
	char *temp_str1 = NULL;
	char *temp_str2 = NULL;
	char *origin1 = NULL; 
	char *origin2 = NULL; 
	int value = 0;
	
	assert(NULL != str1);
	assert(NULL != str2);
	
	temp_str1 = (char *)malloc(StrLen(str1) + 1);
	temp_str2 = (char *)malloc(StrLen(str2) + 1);
	
	/*Saving the address of the strings beginning:*/
	origin1 = temp_str1; 
	origin2 = temp_str2; 
	
	while ('\0' != *str1)
	{
		if(*str1 >= 'A' && *str1 <= 'Z')
		{
		/*Converting the strings upper case letters to lower case*/
			*temp_str1 = *str1 + 32;
		}
		else 
		{
			*temp_str1 = *str1;
		}
		temp_str1++;
		str1++;
	}
	*temp_str1 = '\0';
	temp_str1 = origin1;
	
	while ('\0' != *str2++)
	{
		if(*str2 >= 'A' && *str2 <= 'Z')
		{
			*temp_str2 = *str2 + 32;
		}
		else 
		{
			*temp_str2 = *str2;
		}
		temp_str2++;
	}
	*temp_str2 = '\0';
	temp_str2 = origin2;
	
	value = StrCmp(temp_str1, temp_str2);
	
	free(temp_str1); 
	free(temp_str2); 
			
	return (value);
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
	
	while('\0' != *source && iterations > 0)
	{
		*destination = *source;
		source++;
		destination++;
		iterations--;
	}
	*destination = '\0';
	
	/*Paddeing The rest of the memmory in destination with null characters*/
	while('\0' != *source)
	{
		*destination = '\0';
		destination++;
		source++;
	}
	
	return (origin);
}

char *StrChar(const char *str, int sign)
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

/*Importent! when using StrDup the user is responsible for freeing the memory!*/
char *StrDup(const char *str)
{
	char *duplicated = NULL;
	char *origin = NULL;
	
	assert(NULL != str);
	
	duplicated = (char *)malloc(StrLen(str) + 1);
	origin =  duplicated;
	
	while('\0' != *str)
	{
		*duplicated = *str;
		str++;
		duplicated++;
	}
	*duplicated = '\0';
	
	return (origin);
}

char *StrCat(char *destination, const char *source)
{
	char *origin = NULL;
	
	assert(NULL != destination);
	assert(NULL != source);
	
	origin = destination;
	
	/*Moving the pointer to the end of destination*/
	destination += StrLen(destination);
	
	while('\0' != *source)
	{
		*destination = *source;
		destination++;
		source++;
	}
	*destination = '\0';
	
	return (origin);
}

char *StrNCat(char *destination, const char *source, size_t iterations)
{
	char *origin = NULL;
	
	assert(NULL != destination);
	assert(NULL != source);
	
	origin = destination;
	
	destination += StrLen(destination);
	
	while('\0' != *source && iterations > 0)
	{
		*destination = *source;
		destination++;
		source++;
		iterations--;
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

size_t StrSpn(const char *str1, const char *str2)
{
	size_t counter = 0;
	const char *temp = NULL;
	
	assert(NULL != str1);
	assert(NULL != str2);
	
	while('\0' != *str1)
	{
		temp = StrStr(str1, str2);
		if(NULL != temp)
		{
			counter++;
			/*Use pointer atrithmetics to get past the found substirng 
			str2*/
			str1 = temp + StrLen(str2); 
			if ('\0' == *str1)
			{
				/* If we reached the end of str1 there is nothing 
				left to search */
				break; 
			}	
		}
		else
		{
			break; /*StrStr found no more substirngs str2 in str1*/
		}
	}
	
	return (counter);
}





























