/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
*******************************************************************************/
#include <stdio.h>  /*FILE  */
#include <string.h> /*strcpy*/

#include "ws9.h"

#define NUMBER_OF_STUDENTS 2

output_t SaveToBinFile(student *my_student)
{
	FILE *fp;
	
	fp = fopen("my_student.bin", "w");
	if(!fp)
	{
		return (FILE_ERROR);
	}
	
	fwrite(my_student, sizeof(*my_student), 1, fp);
	
	fclose(fp);
	if(!fp)
	{
		return (FILE_ERROR);
	}
	
	return (SUCCESS);
}

output_t LoadFromBinFile(student *my_student)
{
	FILE *fp;
	
	fp = fopen("my_student.bin", "r");
	if(!fp)
	{
		return (FILE_ERROR);
	}
	
	fread(my_student, sizeof(*my_student), 1, fp);
	
	fclose(fp);
	if(!fp)
	{
		return (FILE_ERROR);
	}
	
	return (SUCCESS);
}

int ManageStudentID()
{
	output_t state = SUCCESS;
	student student_array[NUMBER_OF_STUDENTS]; 
	size_t array_size = 0;
	
	array_size = sizeof(student_array[0]);
	
	/*initializing the student*/
	strcpy(student_array[0].first_name, "John");
	strcpy(student_array[0].last_name, "Smith");
	student_array[0].grades.humanities_grades.sociology = 88.5;
	student_array[0].grades.humanities_grades.psychology = 95.4;
	student_array[0].grades.real_grades.chemistry = 56.3;
	student_array[0].grades.real_grades.physics = 32.9;
	student_array[0].grades.sports_grade = 90.0;
	
	/*saveing the student struct to a binary file*/
	state = SaveToBinFile(&student_array[0]);
	
	/*loading the binary file to a new student struct*/
	state = LoadFromBinFile(&student_array[1]);
	
	/*the structs have the exact same binary data so we can use memcmp*/
	state = memcmp(&student_array[0], &student_array[1], array_size);
	
	return (state);	
}

















