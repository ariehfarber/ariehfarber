/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Artur Livshits
*Date: 15/11/2023
*******************************************************************************/
#ifndef  __WS5_H__
#define __WS5_H__

/*******************************************************************************
*Description: Prints a list of 10 redefined integers.
*******************************************************************************/
void PrintInt();

/*******************************************************************************
*Description: Add text to a file, with 4 command options:
*	  	      '-remove' Deletes the file.
*	    	  '-count' Counts the number of lines.
*	    	  '-exit' Exits the program.
*	   	      '<' adds the text to the beginning of the file.
*	    	  Defualt - the text will be added to the end of the file.
*Return values: If exited successfully, returns 0.
*Notes: The text string is limitid to 100 charecters per input.
*******************************************************************************/
int FileEditor(const char *file);

#endif /*__WS5_H__*/
