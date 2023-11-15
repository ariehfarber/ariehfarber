/***********************************************************************************
*Author: Arieh Farber 
*Reviewer: Artur Livshits
*Date: 
***********************************************************************************/

#include "ws5.h"

void TestPrintInt();
void TestFileEditor();

int main()
{
/*	TestPrintInt();*/
	TestFileEditor();
	
	return (0);
}

/**********************************************************************************
Exercise 1
**********************************************************************************/
void TestPrintInt()
{
	PrintInt();
}

void TestFileEditor()
{
	const char *test1 = "ws5.txt";
	
	FileEditor(test1);
}
