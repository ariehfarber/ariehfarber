/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Artur Livshits
*Date: 15/11/2023
*******************************************************************************/
#include <stdio.h> /*printf*/

#include "ws5.h"

void TestPrintInt();
void TestFileEditor(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	TestPrintInt();
	TestFileEditor(argc, argv);
	
	return (0);
}

void TestPrintInt()
{
	PrintInt();
}

void TestFileEditor(int argc, char *argv[])
{
	if (2 != argc) 
	{
		printf("error with file name\n");
		return;
	}
	
	FileEditor(argv[1]);
}
