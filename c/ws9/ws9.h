/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Dvir Monajem
*Date: 23/11/2023
*******************************************************************************/
#ifndef  __WS9_H__
#define __WS9_H__

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
*Description: saves a student struct to a binary file
*Return values: success - 0
		fail    - non-zero
*******************************************************************************/
int SaveToBinFile(student *my_student, char *title);

/*******************************************************************************
*Description: loads a student struct from a binary file
*Return values: success - 0
		fail    - non-zero
*******************************************************************************/
int LoadFromBinFile(student *my_student, char *title);

#endif /*__WS9_H__*/
