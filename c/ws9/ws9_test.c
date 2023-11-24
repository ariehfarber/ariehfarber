/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Dvir Monajem
*Date: 23/11/2023
*******************************************************************************/
#include <stdio.h>  /*printf*/
#include <string.h> /*memcmp*/

#include "ws9.h"

static void TestManageStudent();

int main()
{
	TestManageStudent();
	
	return (0);
}

static void TstResInt(int control, int func_res, int line)
{
	if (control != func_res)
	{
		printf("\033[0;31m");
		printf("Error. failed at line %d\n", line);
		printf("\033[0m"); 
	}
}

static void TestManageStudent()
{
	int state = -1;
	int control = 0;
	size_t struct_size = 0;
	student original_student = {"John", "Smith", {{88.5, 95.4},\
				   {56.3, 32.9}, 90.0}};
	student copied_student;  

	struct_size = sizeof(original_student);
	
	/*saveing the student struct to a binary file*/
	state = SaveToBinFile(&original_student, "student.bin");
	
	/*loading the binary file to a new student struct*/
	state = LoadFromBinFile(&copied_student, "student.bin");
	
	/*the structs have the exact same binary data so we can use memcmp*/
	state = memcmp(&original_student, &copied_student, struct_size);
	
	TstResInt(control, state, __LINE__);
}
