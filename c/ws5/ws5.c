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
Exercise 1
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
Exercise 2 - phase 1
**********************************************************************************/
void FileEditorPhase1(const char *file_name)
{
	char string[85] = {0};
	FILE *test_file;
	
	test_file = fopen(file_name, "a");
	if(!test_file)
	{
		printf("error with fopen");
		return;
	}
	
	printf("Enter string (up to 85 charecters):\n");
	if(!fgets(string, 85, stdin))
	{
		printf("error with fgets");
		return;
	}

	fputs(string, test_file);
	
	fclose(test_file);
	if(!test_file)
	{
		printf("error with fclose");
		return;
	}
}

/**********************************************************************************
Exercise 2 - phase 2
**********************************************************************************/
typedef int (*PFnComparison)(const char *, const char *);
typedef void (*PFnOperation)(const char *);

typedef struct special_input
{
	char *str;
	PFnComparison Comparison;
	PFnOperation Operation;
} special_input;

int StrCmp(const char *str1, const char *str2)
{
	assert(NULL != str1);
	assert(NULL != str2);
	
	while(*str1 == *str2 && '\0' != *str1)
	{
		str1++;
		str2++;	
	}
			
	return (*str1 - *str2);
}

void RemoveCommand(const char *file_name)
{
	int ret;
	
	ret = remove(file_name);
	  
	if(ret == 0) 
	{
		printf("File deleted successfully\n");
	} 
	else 
	{
		printf("Error: unable to delete the file\n");
	}	
}

void CountCommand(const char *file_name)
{
	int count = 0;
	int ret;
	char c;
	FILE *test_file;
	
	test_file = fopen(file_name, "r");
	if(!test_file)
	{
		printf("error with fopen\n");
		return;
	}
	
	for (c = getc(test_file); c != EOF; c = getc(test_file))
	{
		if (c == '\n')
		{
			count++;
		}
	}
	
	ret = fclose(test_file);
	if(ret == 0) 
	{
		printf("File closed successfully\n");
	} 
	else 
	{
		printf("Error: unable to close the file\n");
	}
	
	printf("The file %s has %d lines\n", file_name, count);
}

void ExitCommand(const char *file_name)
{
	(void)file_name;
	exit(0);
}

/*void AddToStartCommand(const char *file_name)*/
/*{*/

/*}*/

void FileEditor(const char *file_name)
{
	char string[85] = {0};
	int i = 0;
	int size = 3;
	char *command[3] = {"-remove", "-count", "-exit"};
	special_input array[4];
	
	for(i = 0; i < size; i++)
	{
		array[i].str = command[i];
		array[i].Comparison = StrCmp;
	}
	
	array[0].Operation = RemoveCommand;
	array[1].Operation = CountCommand;
	array[2].Operation = ExitCommand;
	
	printf("Enter string (up to 85 charecters):\n");
	if(!fgets(string, 85, stdin))
	{
		printf("error with fgets");
		return;
	}
	
	for(i = 0; i < size; i++)
	{
		if(!array[i].Comparison(array[i].str, string))
		{
			array[i].Operation(file_name);
		}
	}	
}


	



































