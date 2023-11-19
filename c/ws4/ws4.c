/***********************************************************************************
*Author: Arieh Farber 
*Reviewer: Artur Livshits
*Date: 13/11/2023
***********************************************************************************/

#include <stdio.h>  /*printf, getchar*/
#include <stdlib.h> /*system*/

#include "ws4.h"

#define ESC 27
#define SIZE_OF_ASCII 256

typedef void (*PFnPrintFunctions[SIZE_OF_ASCII])(void);

/**********************************************************************************
Exercise Switch
**********************************************************************************/
void SwitchKeyInputAT()
{
	int c = 0;

	if(system("stty -icanon -echo"))
	{
		printf("Issue with system command\n");
		return;
	}
	
	printf("Switch function:\n");
	while(ESC != c)
	{
		printf( "Press A or T keys to activate:\n");
		c = getchar( );
		
		switch(c)
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
	
	if(system("stty -icanon -echo"))
	{
		printf("Issue with system command\n");
		return;
	}
}

/**********************************************************************************
Exercise If
**********************************************************************************/
void IfKeyInput()
{
	int c = 0;
	
	if(system("stty -icanon -echo"))
	{
		printf("Issue with system command\n");
		return;
	}
	
	printf("if function:\n");
	while(ESC != c)
	{
		printf( "Press A or T keys to activate:\n");
		c = getchar( );
				
		if(c == 'A' || c == 'a')
		{
			printf("A-pressed\n");
		}
		
		if(c == 'T' || c == 't')
		{
			printf("T-pressed\n");
		}

	} 
	
	if(system("stty -icanon -echo"))
	{
		printf("Issue with system command\n");
		return;
	}
}

/**********************************************************************************
*Print functions for LUT function
**********************************************************************************/
void PrintA()
{
	printf("A-pressed\n");
}

void PrintT()
{
	printf("T-pressed\n");
}

void EmptyFunction()
{
}

/**********************************************************************************
Exercise LUT
**********************************************************************************/
void LUTKeyInput()
{
	int c = 0;
	int i = 0;
	
	/*Array of function pointers*/
	PFnPrintFunctions PrintLetter;
	
	if(system("stty -icanon -echo"))
	{
		printf("Issue with system command\n");
		return;
	}
	
	/*Padding the array with empty functions*/
	for(i = 0; i < 256; i++)
	{
		PrintLetter[i] = EmptyFunction;
	}
	
	/*Assigning the print functions to the function pointers*/
	PrintLetter[(unsigned char)'A'] = PrintA;
	PrintLetter[(unsigned char)'a'] = PrintA;
	PrintLetter[(unsigned char)'T'] = PrintT;
	PrintLetter[(unsigned char)'t'] = PrintT;
	
	printf("LUT function:\n");
	while(ESC != c)
	{
		printf( "Press A or T keys to activate:\n");

		c = getchar( );
		PrintLetter[(unsigned char)c]();
	} 
	
	if(system("stty -icanon -echo"))
	{
		printf("Issue with system command\n");
		return;
	}
}

































