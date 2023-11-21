/***********************************************************************************
*Author: Arieh Farber 
*Reviewer: 
*Date: 
***********************************************************************************/

#include <stdio.h>  /*printf			*/
#include <stdlib.h> /*size_t,malloc,realloc,free*/
#include <assert.h> /*assert			*/
#include <string.h> /*strlen,strcat		*/

#include "ws7.h"

#define ELEMENT_NUM 5

typedef void (*PFnPrint)(size_t);
typedef void (*PFnAdd)(size_t *, int);
typedef void (*PFnClean)(size_t *);

typedef struct element
{
	size_t data;
	PFnPrint PrintValue;
	PFnAdd AddNumber;
	PFnClean CleanValue;
} element_t;

void SetInt(element_t *target, int int_number) 
{
	target->data = *(size_t *)&int_number; 
}

void SetFloat(element_t *target, float float_number) 
{
	target->data = *(size_t *)&float_number;
}

void SetString(element_t *target, char *str) 
{
	target->data = (size_t)str; 
}

void PrintInt(size_t value)
{
	printf("%d, ", *(int *)&value);	
}

void PrintFloat(size_t value)
{
	printf("%.6f, ", *(float *)&value);	
}

void PrintString(size_t value)
{
	printf("%s, ", (char *)value);	
}

void AddInt(size_t *target, int int_value)
{
	int temp_int = 0;
	
	temp_int = *(int *)target;
	temp_int += int_value;
	*target = *(size_t *)&temp_int;	
}

void AddFloat(size_t *target, int float_value)
{
	float temp_float = 0;
	
	temp_float = *(float *)target;
	temp_float += (float)float_value;
	*target = *(size_t *)&temp_float;	
}

void AddString(size_t *target, int value)
{
	char temp_buffer[11];
	char *new_str = NULL;
	size_t new_str_length = 0;

	/*convert int to char*/
	sprintf(temp_buffer, "%d", value);

	 /*+1 for NULL terminator*/
	new_str_length = strlen((char *)(*target)) + strlen(temp_buffer) + 1;

	new_str = realloc(((char *)(*target)), new_str_length);
	assert(new_str);

	/*concatenate the string with the number*/
	strcat(new_str, temp_buffer);

	/*set the struct pointer to the concatenated string*/
	*target = (size_t)new_str;
}

void CleanInt(size_t *target)
{
	(void)target;
}

void CleanFloat(size_t *target)
{
	(void)target;
}

void CleanString(size_t *target)
{
	free((char *)(*target));
	*target = '\0'; 
}

void ListElements()
{		
	int i = 0;
	char *string = NULL;
	
	/*initialize struct array*/
	element_t element_array[ELEMENT_NUM] =
	{
		{0, PrintFloat, AddFloat, CleanFloat},
		{0, PrintInt, AddInt, CleanInt},
		{0, PrintInt, AddInt, CleanInt},
		{0, PrintFloat, AddFloat, CleanFloat},
		{0, PrintString, AddString, CleanString}
	}; 
	
	string =  malloc(sizeof(char *) * strlen("chapter") + 1);
	assert(string);
	
    	strcpy(string, "chapter");

	SetFloat(&element_array[0], 4.212212);
	SetInt(&element_array[1], 500);
	SetInt(&element_array[2], 12);
	SetFloat(&element_array[3], 56.32);
	SetString(&element_array[4], string);
	
	for(i = 0; i < ELEMENT_NUM; i++)
	{
		element_array[i].PrintValue(element_array[i].data);
	}
	printf("\n");
	
	for(i = 0; i < ELEMENT_NUM; i++)
	{
		element_array[i].AddNumber(&element_array[i].data, 10);
	}
	
	for(i = 0; i < ELEMENT_NUM; i++)
	{
		element_array[i].PrintValue(element_array[i].data);
	}
	printf("\n");
	
	for(i = 0; i < ELEMENT_NUM; i++)
	{
		element_array[i].CleanValue(&element_array[i].data);
	}
}

