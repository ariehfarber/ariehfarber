/*******************************************************************************
*Author: Arieh Farber
*Reviewer: Artur Livshits
*Date: 13/11/2023
*******************************************************************************/

#include "ws4.h"

void TestSwitchKeyInputAT();
void TestIfKeyInput();
void TestLUTKeyInput();

int main()
{
	TestSwitchKeyInputAT();
	TestIfKeyInput();
	TestLUTKeyInput();
	
	return (0);
}

/*******************************************************************************
Exercise Switch
*******************************************************************************/
void TestSwitchKeyInputAT()
{
	SwitchKeyInputAT();
}

/*******************************************************************************
Exercise if
*******************************************************************************/
void TestIfKeyInput()
{
	IfKeyInput();
}

/*******************************************************************************
Exercise LUT
*******************************************************************************/
void TestLUTKeyInput()
{
	LUTKeyInput();
}
