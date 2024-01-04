/*******************************************************************************
*Author: 
*******************************************************************************/
#include <stdio.h> /*printf*/

#include "calculator.h"

int main()
{
	status_t my_status = SUCCESS;
	double res = 0;
	
	my_status = Calculate("7+8", &res);
	
	if (SUCCESS == my_status)
	{
		printf("Result = %f status = %d\n", res, my_status);
	}
	else
	{
		printf("status = %d\n", my_status);
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
