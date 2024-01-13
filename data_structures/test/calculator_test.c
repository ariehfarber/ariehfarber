/*******************************************************************************
*Author: Arieh Farber
*******************************************************************************/
 #include <stdio.h> /* printf */

#include "calculator.h"
#include "ds_utils.h" /* TestInt, TestDouble */ 

 static void TestCalculate();

int main()
{
	TestCalculate();
	
	return (0);
}

static void TestCalculate()
{
	status_t got_status = 0;
	status_t want_status[] = {SUCCESS, SUCCESS, SYNTAX_ERROR, MATH_ERROR, \
						 	  SUCCESS, SYNTAX_ERROR, SYNTAX_ERROR, SUCCESS};
	char *expressions[] = {"7+8", "8+83+-2^5", "8+83-2^", "5+2/0", \
						   "8++8((3-2)5)", "3-2)5", "(3-2)5+ 5(4+4+4", \
						   "(1+3)/5"};
	double res = 0;
	double want_res[] = {15.0, 59.0, 0, 0, 48.0, 0, 0, 0.8};
	size_t expressions_size = sizeof(expressions) / sizeof(expressions[0]);
	size_t i = 0;
	
	for (i = 0; i < expressions_size; ++i)
	{
		got_status = Calculate(expressions[i], &res);
		TestInt(want_status[i], got_status, __LINE__);
		TestDouble(want_res[i], res, __LINE__);
		printf("\n");
	}
} 

/*******************************************************************************
 * Author: Yael Argov
 ******************************************************************************/

/*#include <stdio.h>   fgets, printf	   
#include <string.h>  strcmp, strcoy */

/* #include "calculator.h"

#define FALSE 0
#define TRUE 1
#define IS_MATCH 0
#define QUIT "q\n"
#define MAX_STRING_LENGTH 200

void GetErrorDescription(char *dest, status_t status)
{
	static char error_array[4][20];
	static int is_initialized = FALSE;
	if (FALSE == is_initialized)
	{
		strcpy(error_array[SUCCESS], "success!");
		strcpy(error_array[MATH_ERROR], "math_error!");
		strcpy(error_array[SYNTAX_ERROR], "syntax error!");
		strcpy(error_array[ALLOCATION_ERROR], "allocation error!");
		is_initialized = TRUE;
	}
	strcpy(dest, error_array[status]);
}		

int main()
{
	char expression[MAX_STRING_LENGTH];
	char error[MAX_STRING_LENGTH];
	double result;
	status_t status;
	printf("enter expressions to caculate or type 'q' to exit:\n\n");
	fgets(expression, MAX_STRING_LENGTH, stdin);
	while (IS_MATCH != strcmp(expression, QUIT)) 
	{

		status = Calculate(expression, &result);
		if (SUCCESS != status)
		{
			GetErrorDescription(error, status);
			printf("%s\n\n", error);
		}
		else
		{
			printf("result is %.2f\n\n", result);
		}
		fgets(expression, MAX_STRING_LENGTH, stdin);
	} 

	return (0);
} */



