/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Artur Livshits
*Date: 13/11/2023
*******************************************************************************/
#include <stdio.h>  /*printf, getchar*/
#include <stdlib.h> /*system*/

#include "ws4.h"

#define ESC_KEY 27
#define SIZE_OF_ASCII 256

typedef void (*PFnPrintFunctions[SIZE_OF_ASCII])(void);

static void PrintA();
static void PrintT();
static void EmptyFunction();

void SwitchKeyInputAT()
{
	int c = 0;

	if (system("stty -icanon -echo"))
	{
		printf("Issue with system command\n");
		return;
	}
	
	printf("Switch function:\n");
	while (ESC_KEY != c)
	{
		printf( "Press A or T keys to activate, and Esc key to exit:\n");
		c = getchar( );
		
		switch (c)
		{
			case ('A'):
			case ('a'):
				printf("A-pressed\n");
				break;		
			
			case ('T'):
			case ('t'):
				printf("T-pressed\n");
				break;
		}
	} 
	
	if (system("stty icanon echo"))
	{
		printf("Issue with system command\n");
		return;
	}
}

void IfKeyInput()
{
	int c = 0;
	
	if (system("stty -icanon -echo"))
	{
		printf("Issue with system command\n");
		return;
	}
	
	printf("if function:\n");
	while (ESC_KEY != c)
	{
		printf( "Press A or T keys to activate, and Esc key to exit:\n");
		c = getchar( );
				
		if (c == 'A' || c == 'a')
		{
			printf("A-pressed\n");
		}
		
		if (c == 'T' || c == 't')
		{
			printf("T-pressed\n");
		}
	} 
	
	if (system("stty icanon echo"))
	{
		printf("Issue with system command\n");
		return;
	}
}

void LUTKeyInput()
{
	int c = 0;
	int i = 0;
	
	PFnPrintFunctions PrintLetter;
	
	if (system("stty -icanon -echo"))
	{
		printf("Issue with system command\n");
		return;
	}
	
	for (i = 0; i < 256; ++i)
	{
		PrintLetter[i] = EmptyFunction;
	}
	
	PrintLetter[(unsigned char)'A'] = PrintA;
	PrintLetter[(unsigned char)'a'] = PrintA;
	PrintLetter[(unsigned char)'T'] = PrintT;
	PrintLetter[(unsigned char)'t'] = PrintT;
	
	printf("LUT function:\n");
	while (ESC_KEY != c)
	{
		printf( "Press A or T keys to activate, and Esc key to exit:\n");

		c = getchar( );
		PrintLetter[(unsigned char)c]();
	} 
	
	if (system("stty icanon echo"))
	{
		printf("Issue with system command\n");
		return;
	}
}

static void PrintA()
{
	printf("A-pressed\n");
}

static void PrintT()
{
	printf("T-pressed\n");
}

static void EmptyFunction()
{
}
