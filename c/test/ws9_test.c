/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Dvir Monajem
*Date: 23/11/2023
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <string.h> /*memcmp*/

#include "ws9.h"

#define SUCCESS 0
#define FAILURE 1

static void TestManageStudent();

int main()
{
	TestManageStudent();
	
	return (0);
}

static void TestInt(int want, int got, int line);

static void TestManageStudent()
{
	int state = -1;
	size_t struct_size = 0;
	student original_student = {"John", "Smith", {{88.5, 95.4},\
				   			   {56.3, 32.9}, 90.0}};
	student copied_student;  

	struct_size = sizeof(original_student);
	
	state = SaveToBinFile(&original_student, "student.bin");
	TestInt(SUCCESS, state, __LINE__);
	
	state = LoadFromBinFile(&copied_student, "student.bin");
	TestInt(SUCCESS, state, __LINE__);
	
	state = memcmp(&original_student, &copied_student, struct_size);
	TestInt(SUCCESS, state, __LINE__);
}

static void TestInt(int want, int got, int line)
{
	if (want != got)
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
