/*******************************************************************************
*Author: 
*******************************************************************************/
#include <stdio.h> /*printf*/

#include "calculator.h"

int main()
{
	status_t my_status = SUCCESS;
	double res = 0;
	char *want_array[] = {"8+83-2/(5*2)"};
	size_t want_array_size = sizeof(want_array) / sizeof(want_array[0]);
	size_t i = 0;
	
	for (i = 0; i < want_array_size; ++i)
	{
		my_status = Calculate(want_array[i], &res);

		if (SUCCESS == my_status)
		{
			printf("Result = %f status = %d\n", res, my_status);
		}
		else if(MATH_ERROR == my_status)
		{
			printf("Result = %.0f status = MATH_ERROR\n", res);
		}
		else if(SYNTAX_ERROR == my_status)
		{
			printf("Result = %.0f status = SYNTAX_ERROR\n", res);
		}
		else if(ALLOCATION_ERROR == my_status)
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
