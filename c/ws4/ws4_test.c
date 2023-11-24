/*******************************************************************************
*Author: Arieh Farber
*Reviewer: Artur Livshits
*Date: 13/11/2023
*******************************************************************************/
#include "ws4.h"

static void TestSwitchKeyInputAT();
static void TestIfKeyInput();
static void TestLUTKeyInput();

int main()
{
	TestSwitchKeyInputAT();
	TestIfKeyInput();
	TestLUTKeyInput();
	
	return (0);
}

static void TestSwitchKeyInputAT()
{
	SwitchKeyInputAT();
}

static void TestIfKeyInput()
{
	IfKeyInput();
}

static void TestLUTKeyInput()
{
	LUTKeyInput();
}
