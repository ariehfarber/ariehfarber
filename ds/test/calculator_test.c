/*******************************************************************************
*Author: Arieh Farber
*******************************************************************************/
#include <stdio.h> /*printf*/

#include "calculator.h"

int main()
{
	double res = 0;
	status_t got_status = 0;
	char *expressions[] = {"7+8", "8+83+-2^5", "8+83-2^", "2/0", \
						   "8++8((3-2)5)", "3-2)5", "(3-2)5+ 5(4+4+4"};
	double want_res[] =   {15, 49, 0, 0, \
						   48, 0, 0};
	int want_status[] =	  {SUCCESS, SUCCESS, SYNTAX_ERROR, MATH_ERROR, \
						   SUCCESS, SYNTAX_ERROR, SYNTAX_ERROR};
	size_t expressions_array_size = sizeof(expressions_array) / sizeof(expressions_array[0]);
	size_t i = 0;
	
	for (i = 0; i < expressions_array_size; ++i)
	{
		got_status = Calculate(want_array[i], &res);

		if (SUCCESS == got_status)
		{
			printf("Result = %f status = %d\n", res, got_status);
		}
		else if(MATH_ERROR == got_status)
		{
			printf("Result = %.0f status = MATH_ERROR\n", res);
		}
		else if(SYNTAX_ERROR == got_status)
		{
			printf("Result = %.0f status = SYNTAX_ERROR\n", res);
		}
		else if(ALLOCATION_ERROR == got_status)
		{
			printf("Result = %.0f status = ALLOCATION_ERROR\n", res);
		}	
	}
	
	return (0);
}

/*"7+8";                   Result = 15 status = SUCCESS       */
/*"8+83+-2^5";            Result =  0 status = SUCCESS      */
/*"8+83-2^";              Result =  0 status = SYNTAX_ERROR */
/*"2/0";                   Result =  0 status = MATH_ERROR   */
/*"8++8((3-2)5)";        Result = 48 status = SUCCESS       */
/*"3-2)5";                Result =  0 status = SYNTAX_ERROR */
/*"(3-2)5+ 5(4+4+4";     Result =  0 status = SYNTAX_ERROR */
