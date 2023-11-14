/***********************************************************************************
*Author: Arieh Farber 
*Reviewer: Artur Livshits
*Date: 
***********************************************************************************/

#include "ws5.h"

void TestPrintInt();
void TestFileEditorPhase1();
void TestFileEditor();

int main()
{
/*	TestPrintInt();*/
/*	TestFileEditorPhase1();*/
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

void TestFileEditorPhase1()
{
	const char *test1 = "ws5.txt";
	
	FileEditorPhase1(test1);
}

void TestFileEditor()
{
	const char *test1 = "ws5.txt";
	
	FileEditor(test1);
}
