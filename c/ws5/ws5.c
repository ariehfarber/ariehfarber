/***********************************************************************************
*Author: Arieh Farber 
*Reviewer: Artur Livshits
*Date: 
***********************************************************************************/

#include <stdio.h> /*printf, FILE, remove*/
#include <stdlib.h>  /*exit*/
#include <assert.h>  /*assert*/
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
typedef int (*PFnComparison)(const char *, const char *);
typedef enum output (*PFnOperation)(const char *);

typedef struct special_input
{
	char *str;
	PFnComparison Comparison;
	PFnOperation Operation;
} special_input;

char string[85] = {0};

/**********************************************************************************
*Exercise 2 - Error message functions
**********************************************************************************/
enum output FileErrorMessage(FILE *test_file)
{
	if(!test_file)
	{
		printf("error with file function\n");
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
*Exercise 2 - Comparison function
**********************************************************************************/
int StrFileEditorCmp(const char *str1, const char *str2)
{
	assert(NULL != str1);
	assert(NULL != str2);
		
	if('<' == *str1 && '<' == *str2)
	{
		return (0);
	}
	
	while(*str1 == *str2 && '\0' != *str1)
	{
		str1++;
		str2++;	
	}
			
	return (*str1 - *str2);
}

/**********************************************************************************
*Exercise 2 - Operation functions
**********************************************************************************/
enum output RemoveCommand(const char *file_name)
{
	int ret;
	
	ret = remove(file_name);
	RemoveFileError(ret);
	
	return SUCCESS;
}

enum output CountCommand(const char *file_name)
{

	int count = 0;
	char c;
	FILE *test_file;
	
	test_file = fopen(file_name, "r");
	FileErrorMessage(test_file);
	
	for (c = getc(test_file); c != EOF; c = getc(test_file))
	{
		if (c == '\n')
		{
			count++;
		}
	}
	
	fclose(test_file);
	FileErrorMessage(test_file);
	
	printf("The file %s has %d lines\n", file_name, count);
	
	return SUCCESS;
}

enum output ExitCommand(const char *file_name)
{
	(void)file_name;
	return EXIT;
}

enum output AddToStartCommand(const char *file_name)
{
	char ch;
	char *temp_name = "temp.txt";
    	FILE *temp_file;
    	FILE *test_file; 
    	
    	temp_file = fopen(temp_name, "w");
	FileErrorMessage(temp_file);
	
	test_file = fopen(file_name, "r");
	FileErrorMessage(test_file);
	
	fputs(string + 2, temp_file);
	
	while ((ch = fgetc(test_file)) != EOF)
	{
		fputc(ch, temp_file);
	}
	
	fclose(temp_file);
	FileErrorMessage(temp_file);
		
	fclose(test_file);
	FileErrorMessage(test_file);
	
	RemoveCommand(file_name);
	
	if(rename(temp_name, file_name))
	{
		printf("error with rename\n");
		return ERROR;
	}
	
	return SUCCESS;	
}

enum output WriteCommand(const char *file_name)
{
	FILE *test_file;
	
	test_file = fopen(file_name, "a");
	FileErrorMessage(test_file);
	
	fputs(string, test_file);
	
	fclose(test_file);
	FileErrorMessage(test_file);
	
	return SUCCESS;
}

/**********************************************************************************
*Exercise 2 - chain of responsibility function
**********************************************************************************/
void FileEditor(const char *file_name)
{
	int i = 0;
	int size = 4;
	char *cmnd[4] = {"-remove\n", "-count\n", "-exit\n", "<"};
	enum output state = SUCCESS;
	special_input cmnd_array[5];

	cmnd_array[0].str = cmnd[0];
	cmnd_array[1].str = cmnd[1];
	cmnd_array[2].str = cmnd[2];
	cmnd_array[3].str = cmnd[3];
	cmnd_array[4].str = NULL;
	
	cmnd_array[0].Comparison = StrFileEditorCmp;
	cmnd_array[1].Comparison = StrFileEditorCmp;
	cmnd_array[2].Comparison = StrFileEditorCmp;
	cmnd_array[3].Comparison = StrFileEditorCmp;
	cmnd_array[4].Comparison = NULL;
	
	cmnd_array[0].Operation = RemoveCommand;
	cmnd_array[1].Operation = CountCommand;
	cmnd_array[2].Operation = ExitCommand;
	cmnd_array[3].Operation = AddToStartCommand;
	cmnd_array[4].Operation = WriteCommand;
	
	while(state != EXIT)
	{
		printf("Enter string (up to 85 charecters):\n");
		if(!fgets(string, 85, stdin))
		{
			printf("error with fgets");
			return;
		}
		
		for(i = 0; i < size; i++)
		{
			if(!cmnd_array[i].Comparison(cmnd_array[i].str, string))
			{
				state = cmnd_array[i].Operation(file_name);
				break;
			}
			if(4 == (i+1))
			{
				state = cmnd_array[i+1].Operation(file_name);
			}
		}			
	}	
}




	




































