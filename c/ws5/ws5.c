/***********************************************************************************
*Author: Arieh Farber 
*Reviewer: Artur Livshits
*Date: 15/11/2023
***********************************************************************************/

#include <stdio.h> /*printf, FILE, remove, size_t*/
#include <string.h>  /*strncmp, strlen*/
#include "ws5.h"

/**********************************************************************************
*Exercise 1
**********************************************************************************/
typedef void (*PFnPrint)(int);

typedef struct print_me
{
	int number;
	PFnPrint StrPrint;
} print_me;

void Print(int n)
{
	printf("%d\n", n);
}

void PrintInt()
{
	int i = 0;
	int size = 10;
	print_me array[10];

	for(i = 0; i < size; i++)
	{
		array[i].number = i * 5;
		array[i].StrPrint = Print;
		array[i].StrPrint(array[i].number);	
	}
	
}

/**********************************************************************************
*Exercise 2 
**********************************************************************************/
enum output
{
	SUCCESS,
	ERROR,
	EXIT
};

typedef int (*PFnComparison)(const char *, const char *, size_t);
typedef enum output (*PFnOperation)(const char *);

typedef struct special_input
{
	char *str;
	PFnComparison Comparison;
	PFnOperation Operation;
} special_input;

char string[100] = {0};

/**********************************************************************************
*Exercise 2 - Operation error message functions
**********************************************************************************/
enum output FileErrorMessage(FILE *test_file)
{
	if(!test_file)
	{
		printf("error with a file function\n");
		return ERROR;
	}
	
	return SUCCESS;
}

enum output RemoveFileError(int ret)
{
	if(ret != 0) 
	{
		printf("Error: unable to delete the file\n");
		return ERROR;
	}
	
	return SUCCESS;
}

/**********************************************************************************
*Exercise 2 - Operation functions
**********************************************************************************/
enum output RemoveCommand(const char *title)
{
	int check;
	
	check = remove(title);
	RemoveFileError(check);
	
	return SUCCESS;
}

enum output CountCommand(const char *title)
{

	int count = 0;
	char c;
	FILE *test_file;
	
	test_file = fopen(title, "r");
	FileErrorMessage(test_file);
	
	/*Counting the lines using a for() loop*/
	for (c = getc(test_file); c != EOF; c = getc(test_file))
	{
		if (c == '\n')
		{
			count++;
		}
	}
	
	fclose(test_file);
	FileErrorMessage(test_file);
	
	printf("The file %s has %d lines\n", title, count);
	
	return SUCCESS;
}

enum output ExitCommand(const char *title)
{
	(void)title;
	return EXIT;
}

enum output AddToStartCommand(const char *title)
{
	char ch;
	char *temp_title = "temp.txt";
    	FILE *temp_file;
    	FILE *test_file; 
    	
	/*Creating a temporary file and opening the original file*/
    	temp_file = fopen(temp_title, "w+");
	FileErrorMessage(temp_file);
	
	test_file = fopen(title, "r+");
	FileErrorMessage(test_file);
	
	/*Inserting the string as the first line of the temporary file*/
	fputs(string + 2, temp_file);
	
	/*copying the original file into the temporary file*/
	while ((ch = fgetc(test_file)) != EOF)
	{
		fputc(ch, temp_file);
	}
	
	fclose(temp_file);
	FileErrorMessage(temp_file);
		
	fclose(test_file);
	FileErrorMessage(test_file);
	
	/*Deleting the original file*/
	RemoveCommand(title);
	
	/*Renaming the temporary file with the name of the original file*/
	if(rename(temp_title, title))
	{
		printf("error with rename\n");
		return ERROR;
	}
	
	return SUCCESS;	
}

enum output WriteCommand(const char *title)
{
	FILE *test_file;
	
	test_file = fopen(title, "a");
	FileErrorMessage(test_file);
	
	fputs(string, test_file);
	
	fclose(test_file);
	FileErrorMessage(test_file);
	
	return SUCCESS;
}

/**********************************************************************************
*Exercise 2 - chain of responsibility function
**********************************************************************************/
void FileEditor(const char *title)
{
	int i = 0;
	int size = 4;
	size_t n = 0;
	enum output state = SUCCESS;

	/*initializing the struct*/
	special_input cmnd_array[5] = 
	{
		{"-remove\n", strncmp, RemoveCommand},
		{"-count\n", strncmp, CountCommand},
		{"-exit\n", strncmp, ExitCommand},
		{"<", strncmp, AddToStartCommand},
		{NULL, NULL, WriteCommand}
	};
	
	while(state != EXIT)
	{	
		printf("Enter string (up to 100 charecters):\n");
		if(!fgets(string, 100, stdin))
		{
			printf("error with fgets");
			return;
		}
		
		/*We use n and strncmp to decide which command to use*/
		n = strlen(string);
		if('<' == string[0])
		{
			n = 1;
		}
		
		for(i = 0; i < size; i++)
		{
			if(!cmnd_array[i].Comparison(cmnd_array[i].str, string, n))
			{
				state = cmnd_array[i].Operation(title);
				break;
			}
			if(4 == (i+1))
			{
				state = cmnd_array[i+1].Operation(title);
			}
		}			
	}	
}




	




































