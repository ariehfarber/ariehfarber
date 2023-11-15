/***********************************************************************************
*Author: Arieh Farber 
*Reviewer: Artur Livshits
*Date:
***********************************************************************************/

#ifndef  __WS5_H__
#define __WS5_H__

#include <stdio.h> /*FILE*/

enum output
{
	SUCCESS,
	ERROR,
	EXIT
};

/**********************************************************************************
Exercise 1
**********************************************************************************/
void Print(int n);

void PrintInt();

/**********************************************************************************
Exercise 2
**********************************************************************************/
enum output FileErrorMessage(FILE *test_file);

enum output RemoveFileError(int ret);

int StrFileEditorCmp(const char *str1, const char *str2);

enum output RemoveCommand(const char *file_name);

enum output CountCommand(const char *file_name);

enum output ExitCommand(const char *file_name);

enum output AddToStartCommand(const char *str);

enum output WriteCommand(const char *file_name);

void FileEditor(const char *file);

#endif /*__WS5_H__*/
