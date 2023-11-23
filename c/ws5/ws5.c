/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Artur Livshits
*Date: 15/11/2023
*******************************************************************************/

#include <stdio.h>  /*printf, FILE*, remove, size_t, fopen, fclose, getc,
		      gets, fputs                                           */
#include <string.h> /*strncmp, strlen                                       */

#include "ws5.h"

#define COMMANDS_NUM 	 5   /*number of command option    */
#define INPUT_MAX_LENGTH 100 /*maximum input charecters*/

char string[INPUT_MAX_LENGTH] = {0};

typedef void (*PFnPrint)(int);

typedef struct print_me
{
	int number;
	PFnPrint StrPrint;
} print_me_t;

typedef enum output
{
	SUCCESS = 0,
	REMOVE_ERROR = 1,
	FILE_ERROR = 2,
	RENAME_ERROR = 3,
	INPUT_ERROR = 4,
	EXIT = 5
} output_t;

typedef int (*PFnComparison)(const char *, const char *, size_t);
typedef output_t (*PFnOperation)(const char *);

typedef struct special_input
{
	char *str;
	PFnComparison Comparison;
	PFnOperation Operation;
} special_input_t;

/*******************************************************************************
*Exercise 1
*******************************************************************************/
void Print(int n)
{
	printf("%d\n", n);
}

void PrintInt()
{
	int i = 0;
	int size = 10;
	print_me_t array[10];

	for(i = 0; i < size; i++)
	{
		array[i].number = i * 5;
		array[i].StrPrint = Print;
		array[i].StrPrint(array[i].number);	
	}
	
}

/*******************************************************************************
*Exercise 2 - Operation functions
*******************************************************************************/
output_t RemoveCommand(const char *title)
{
	if(remove(title)) 
	{
		return (REMOVE_ERROR);
	}
	
	return (SUCCESS);
}

output_t CountCommand(const char *title)
{

	int count = 0;
	char c;
	FILE *test_file;
	
	test_file = fopen(title, "r");
	if(!test_file)
	{
		return (FILE_ERROR);
	}
	
	/*Counting the lines using a for loop*/
	for (c = getc(test_file); c != EOF; c = getc(test_file))
	{
		if (c == '\n')
		{
			count++;
		}
	}
	
	fclose(test_file);
	if(!test_file)
	{
		return (FILE_ERROR);
	}
	
	printf("The file %s has %d lines\n", title, count);
	
	return (SUCCESS);	
}

output_t ExitCommand()
{
	return (EXIT);
}

output_t AddToStartCommand(const char *title)
{
	int ret;
	char ch;
	char *temp_title = "temp.txt";
    	FILE *temp_file;
    	FILE *test_file; 
    	
	/*Creating a temporary file and opening the original file*/
    	temp_file = fopen(temp_title, "w+");
	if(!temp_file)
	{
		return (FILE_ERROR);
	}
	
	test_file = fopen(title, "r+");
	if(!test_file)
	{
		return (FILE_ERROR);
	}
	
	/*Inserting the string as the first line of the temporary file,
	 not icluding the '<' charecter*/
	fputs(string + 1, temp_file);
	
	/*copying the original file into the temporary file*/
	while ((ch = fgetc(test_file)) != EOF)
	{
		fputc(ch, temp_file);
	}
	
	fclose(temp_file);
	if(!temp_file)
	{
		return (FILE_ERROR);
	}
		
	fclose(test_file);
	if(!test_file)
	{
		return (FILE_ERROR);
	}
	
	/*Deleting the original file*/
	RemoveCommand(title);
	
	/*Renaming the temporary file with the name of the original file*/
	ret = rename(temp_title, title);
	if(ret) 
	{
		return (RENAME_ERROR);
	}
		
	return (SUCCESS);	
}

output_t WriteCommand(const char *title)
{
	FILE *test_file;
	
	test_file = fopen(title, "a");
	if(!test_file)
	{
		return (FILE_ERROR);
	}
	
	fputs(string, test_file);
	
	fclose(test_file);
	if(!test_file)
	{
		return (FILE_ERROR);
	}
	
	return (SUCCESS);
}

/*******************************************************************************
*Exercise 2 - chain of responsibility function
*******************************************************************************/
int FileEditor(const char *title)
{
	int i = 0;
	int size = COMMANDS_NUM;
	size_t n = 0;
	output_t state = SUCCESS;

	/*initializing the struct*/
	special_input_t cmnd_array[COMMANDS_NUM] = 
	{
		{"-remove\n", strncmp, RemoveCommand},
		{"-count\n", strncmp, CountCommand},
		{"-exit\n", strncmp, ExitCommand},
		{"<", strncmp, AddToStartCommand},
		{"", strncmp, WriteCommand}
	};
	
	while(SUCCESS == state)
	{	
		printf("Enter string (up to 100 charecters):\n");
		if(!fgets(string, 100, stdin))
		{
			state = INPUT_ERROR;
		}
		
		
		/*using strncmp to help decide which command to use*/
		n = strlen(string);
		if('<' == string[0])
		{
			n = 1;
		}
		
		/*checking which command to use*/
		for(i = 0; i < size; i++)
		{
			if(!cmnd_array[i].Comparison(cmnd_array[i].str,\
			   string, n))
			{
				state = cmnd_array[i].Operation(title);
				break;
			}
			if(4 == i + 1)
			{
				state = cmnd_array[i+1].Operation(title);
			}
		}
		
		switch(state)
		{
			case SUCCESS:
				break;
			
			case REMOVE_ERROR:
				printf("Error with a remove command\n");
				break;
			
			case FILE_ERROR:
				printf("Error with a file command\n");
				break;
		
			case RENAME_ERROR:
				printf("Error with a rename command\n");
				break;
		
			case INPUT_ERROR:
				printf("Error with a input command\n");
				break;
			
			case EXIT:
				return (SUCCESS);
				break;
		}			
	}
	
	return (state);	
}

	




































