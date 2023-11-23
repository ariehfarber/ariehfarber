/*******************************************************************************
*Author: Arieh Farber 
*Reviewer:
*Date: 
*******************************************************************************/

#ifndef  __WS9_H__
#define __WS9_H__

typedef enum output
{
	SUCCESS = 0,
	FILE_ERROR = 1
} output_t;

typedef struct humanistic
{
    float sociology;
    float psychology;
} humanistic;

typedef struct real
{
    float chemistry;
    float physics;
} real;    


typedef struct all_grades
{
    humanistic humanities_grades;
    real real_grades;
    float sports_grade;    
} all_grades;

typedef struct student
{
	char first_name[20];
	char last_name[20];
	all_grades grades;
} student;

/*******************************************************************************
*Description: creates a struct representing a student and his grades.
	      it then saves the student struct to a binary file,
	      and loads the binary file back into a new student struct.
*Return values: success - 0
		error   - non zero
*******************************************************************************/
int ManageStudentID();

#endif /*__WS9_H__*/
















