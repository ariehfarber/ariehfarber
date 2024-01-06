/*******************************************************************************
*Author: Arieh Farber
*******************************************************************************/
#include <stdio.h> /*printf*/

#include "calculator.h"
#include "ds_utils.h" /*TestInt, TestDouble*/

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
	char *expressions[] = {"7+8", "8+83+-2^5", "8+83-2^", "2/0", \
						   "8++8((3-2)5)", "3-2)5", "(3-2)5+ 5(4+4+4", \
						   "(1+3)/5"};
	double res = 0;
	double want_res[] = {15, 49, 0, 0, 48, 0, 0, 0.8};

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



