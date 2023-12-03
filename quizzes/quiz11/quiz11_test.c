/*******************************************************************************
*Auther: Arieh Farber
*******************************************************************************/
#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc*/
#include <string.h> /*strlen*/
#include <stddef.h> /*size_t*/

#include "quiz11.h"

static void TestFlipStrOrder();

int main()
{
	TestFlipStrOrder();
	
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
	else
	{
		printf("\033[1;32m");
		printf("Success!\n");
		printf("\033[0m"); 
	}
}

static void TestFlipStrOrder()
{
	char *str_test = NULL; 
	char str_control[] = "student am i";
	size_t str_length = 0;
	
	str_test = malloc(strlen(str_control) + 1);
    if (!str_test)
    {
        printf("Memory allocation failed\n");
        return; 
    }
    
	str_length = strlen(str_control);
	
	strcpy(str_test,"i am student");

	str_test = FlipStrOrder(str_test, str_length);
	
	TstResChar(str_control, str_test, __LINE__);
	
	free(str_test);
	str_test = NULL;
}



