/*Main*/

#include <stddef.h> /*included for size_t variable type*/
#include <stdio.h> /*included for printf() function*/
#include "string.h"

void TestStrLen();
void TestStrCmp();

int main()
{

	TestStrLen();
	TestStrCmp();
	
	return (0);
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


      























