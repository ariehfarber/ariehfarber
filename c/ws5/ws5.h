/***********************************************************************************
*Author: Arieh Farber 
*Reviewer: Artur Livshits
*Date:
***********************************************************************************/

#ifndef  __WS5_H__
#define __WS5_H__

/**********************************************************************************
Exercise 1
**********************************************************************************/
void Print(int n);

void PrintInt();

/**********************************************************************************
Exercise 2
**********************************************************************************/
void FileEditorPhase1(const char *file);

int StrCmp(const char *str1, const char *str2);

void RemoveCommand(const char *file_name);

void CountCommand(const char *file_name);

void ExitCommand(const char *file_name);

void FileEditor(const char *file);

#endif /*__WS5_H__*/
