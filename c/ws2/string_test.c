/*Functions*/

#include<stdio.h> /*included for printf() function*/
#include<assert.h> /*included for assert() function*/
#include<stddef.h> /*included for size_t variable type*/
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

/*test functions*/

void TestStrLen()
{
	char string[] = "Hello there";
	size_t length = StrLen(string);
	
	printf("The length of \"%s\" is: %lu\n", string, length);
}

void TestStrCmp()
{
	char string1[] = "check";
	char string2[] = "check";
	int value = StrCmp(string1, string2);
	
	if(value > 0)
	{
	printf("string1 is longer\n");
	}
	else if(value < 0)
	{
	printf("string2 is longer\n");
	}
	else if(value == 0)
	{
	printf("strings are equal\n");
	}


 
}


      























