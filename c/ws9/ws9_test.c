/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stdio.h> /*printf*/

#include "ws9.h"

static void TestManageStudentID();

int main()
{
	TestManageStudentID();
	
	return (0);
}

static void TestManageStudentID()
{
	output_t state = SUCCESS;
	
	state = ManageStudentID();
	
	switch(state)
	{
		case SUCCESS:
			break;
		case FILE_ERROR:
			printf("Error with a file command\n");
			break;
		default:
			printf("Error\n");
			break;
	}
}
