/*******************************************************************************
*Auther: Arieh Farber
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <string.h>  /*strcmp*/

#include "quiz9.h"

static void TestRemoveSpaces();

int main()
{
	TestRemoveSpaces();
	
	return (0);
}

static void TstResChar(char *control, char *func_res, int line)
{
	if (strcmp(control, func_res))
	{
		printf("\033[0;31m");
		printf("Error. failed at line %d\n", line);
		printf("\033[0m"); 
	}
}

static void TestRemoveSpaces()
{
	char str1[] = " 	Hello,  world! 	 	";
	char *control = "Hello, world!";
	
	TstResChar(control, RemoveSpaces(str1), __LINE__);
}
