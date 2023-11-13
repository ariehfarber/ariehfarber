/***********************************************************************************
*Author: Arieh Farber 
*Reviewer: Artur Livshits
*Date: 13/11/2023
***********************************************************************************/

#include <stdio.h>  /*printf, getchar*/
#include <stdlib.h>  /*system*/
#include "ws4.h"

typedef void (*PFnPrintFunctions[256])(void);

/**********************************************************************************
Exercise Switch
**********************************************************************************/
void SwitchKeyInput()
{
	int c = 0;
	int check;
	
	check = system("stty -icanon -echo");
	if(-1 == check)
	{
		printf("Issue with system command\n");
		return;
	}
	
	printf("Switch function:\n");
	while(27 != c)
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
	
	system("stty icanon echo");
	if(-1 == check)
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
	int check;
	
	check = system("stty -icanon -echo");
	if(-1 == check)
	{
		printf("Issue with system command\n");
		return;
	}
	
	printf("if function:\n");
	while(27 != c)
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
	
	system("stty icanon echo");
	if(-1 == check)
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
	int check;
	int i = 0;
	
	/*Array of function pointers*/
	PFnPrintFunctions PrintLetter;
	
	check = system("stty -icanon -echo");
	if(-1 == check)
	{
		printf("Issue with system command\n");
		return;
	}
	
	/*Padding the array with empty functions*/
	for(i = 0; i < 256; i++)
	{
		PrintLetter[i] = EmptyFunction;
	}
	
	/*Assigning the print functions*/
	PrintLetter[(unsigned char)'A'] = PrintA;
	PrintLetter[(unsigned char)'a'] = PrintA;
	PrintLetter[(unsigned char)'T'] = PrintT;
	PrintLetter[(unsigned char)'t'] = PrintT;
	
	printf("LUT function:\n");
	while(27 != c)
	{
		printf( "Press A or T keys to activate:\n");
		c = getchar( );
		
		PrintLetter[(unsigned char)c]();
	} 
	
	system("stty icanon echo");
	if(-1 == check)
	{
		printf("Issue with system command\n");
		return;
	}
}

































